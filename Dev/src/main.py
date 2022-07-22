import math
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import itertools as it
from numba import jit
from dataclasses import dataclass, field
from typing import Dict, List, Optional
import pandas as pd

from dataclasses import dataclass, field
from typing import Dict, List, Optional
import pandas as pd
from numpy.linalg import norm
from scipy.spatial import distance
import time

def normalized_cosine_distance(a,b):
    return np.dot(a, b)/(norm(a)*norm(b))

@dataclass
class MicroClusters:
    id: int
    mean: float
    type_distance: str
    variance_limit: float = 0.01
    num_samples: int = 1
    variance: float = 0
    life: float = 1
    decay: Optional[float] = 100
    debug: bool = False
    active: bool = True
    update: bool = True
    last_eccentricity: Optional[float] = None
    last_normalized_eccentricity: Optional[float] = None
    last_tipicality: Optional[float] = None
    last_normalized_tipicality: Optional[float] = None
    last_density: Optional[float] = None
    

    def compute_new_mean(self, x:np.ndarray):
        if self.type_distance == 'Euclidean_distance':
            return (
                ( self.num_samples/(self.num_samples+1) ) * self.mean +
                ( x / (self.num_samples+1) )
            )
        
    def compute_new_variance(self, x:np.ndarray, new_mean:np.ndarray):
        if self.type_distance == 'Euclidean_distance':   
            return (
                ( self.num_samples/(self.num_samples+1) ) * self.variance + 
                ( 1/(self.num_samples) ) * ( ( norm(x-new_mean)*2 / len(x) )** 2 )
            )

 
    def compute_eccentricity(self, x, new_mean:np.ndarray, new_variance:float):
        if self.type_distance == 'Euclidean_distance':
            if new_variance > self.variance_limit and self.num_samples<=3:
                return 1e3
            if new_variance == 0 and self.num_samples+1 > 1:
                return 1/(self.num_samples+1)
            return (
                    1/(self.num_samples+1) + (
                    np.inner((new_mean - x).T, (new_mean - x))) / ( 
                        (self.num_samples+1) * new_variance 
                    )
                )
                
        if self.type_distance == 'Cosine_distance':
            return (
                (
                    (1+ np.dot(new_mean, (x/norm(x))) ) /
                    (1+ self.num_samples * np.dot(new_mean, new_mean))
                )
                if norm(x) > 0 
                else 0
            )
           
    def compute_normalized_eccentricity(self):
        return self.last_eccentricity/2
    
    def compute_last_tipicality(self):
        return (
            1 - self.last_eccentricity if (self.num_samples+1) >= 2 else 0
        )
        
    def compute_normalized_tipicality(self):
        return (
            self.last_tipicality/(self.num_samples+1-2) if (self.num_samples+1) > 2 else 0
        )
    
    def compute_mik_sik(self, s_ik):
        return 3 / (1 + math.exp(-0.007 * (s_ik - 100)))
    
    def is_outlier_eucludean_distance(self, new_variance:float):
        s_ik = self.num_samples+1
        
        if s_ik < 3:
            outlier = (new_variance > self.variance_limit)
            if self.debug:
                print(f's_ik: {s_ik} outlier: {outlier} ')
            return outlier
        
        mik_sik = self.compute_mik_sik(s_ik)
        outlier_limit = ((mik_sik ** 2) + 1) / (2 * s_ik)
        outlier = (self.last_normalized_eccentricity > outlier_limit)
        if self.debug:
            print(f's_ik: {s_ik} outlier: {outlier} ecc_limit: {outlier_limit}, norm_ecc: {self.last_normalized_eccentricity}')
        return outlier
       
    def is_outlier_cosine_distance(self, x, new_mean:np.ndarray, new_variance:float):
        s_ik = self.num_samples+1
        
        if s_ik > 2:
            mik_sik = 3 
            dist_x_mu = normalized_cosine_distance(x,new_mean)** 2
            n_variance = (mik_sik ** 2) * new_variance
            outlier = dist_x_mu > n_variance
            if self.debug:
                print(f's_ik: {s_ik} outlier: {outlier} dist_x_mu: {dist_x_mu}, n_variance: {n_variance}')
            return outlier
            
        mik_sik = self.compute_mik_sik(s_ik) #3
        dist_x_mu = normalized_cosine_distance(x,new_mean)** 2
        n_variance = (mik_sik ** 2) * new_variance
        
        outlier = dist_x_mu > n_variance and (new_variance > self.variance_limit)
        if self.debug:
            print(f's_ik: {s_ik} outlier: {outlier} dist_x_mu: {dist_x_mu}, n_variance: {n_variance}')
        return outlier
      
    def _is_outlier(self, x, new_mean:np.ndarray, new_variance:float):
        if self.type_distance == 'Euclidean_distance':
            return self.is_outlier_eucludean_distance(new_variance)
        if self.type_distance == 'Cosine_distance':
            return self.is_outlier_cosine_distance(x, new_mean, new_variance)
    
    def decline_life_linear(self):
        return self.life - 1/self.decay

    def _update_microcluster(self, _is_oulier:bool, new_mean:np.ndarray, new_variance:float):
        self.num_samples = self.num_samples+1 if not _is_oulier else self.num_samples
        self.mean = new_mean if not _is_oulier else self.mean
        self.variance = new_variance if not _is_oulier else self.variance
        self.life = 1 if not _is_oulier else self.decline_life_linear()
        self.update = not _is_oulier 
                
    def update_microcluster(self, x:np.ndarray, update=True):
        new_mean = self.compute_new_mean(x)
        new_variance = self.compute_new_variance(x,new_mean)
        self.last_eccentricity = self.compute_eccentricity(x, new_mean, new_variance)
        self.last_normalized_eccentricity = self.compute_normalized_eccentricity()
        self.last_tipicality = self.compute_last_tipicality()
        self.last_normalized_tipicality = self.compute_normalized_tipicality()
        self.last_density=1/self.last_normalized_eccentricity
        is_oulier = self._is_outlier(x, new_mean, new_variance)
        if update: 
            self._update_microcluster(is_oulier, new_mean, new_variance)
    
    def has_intersection(self, mi):
        if self.type_distance == 'Euclidean_distance':
            return norm(self.mean - mi.mean) < 2*(self.variance**0.5 + mi.variance**0.5)
        if self.type_distance == 'Cosine_distance':
            return normalized_cosine_distance(
                    self.mean, mi.mean
                ) < 2*(self.variance**0.5 + mi.variance**0.5)
        
    
@dataclass
class EvolvingMicroTEDA:
    type_distance: Optional[str] = 'Euclidean_distance'
    microclusters: Optional[List[MicroClusters]] = None
    macroclusters: Optional[List[int]] = None
    debug: bool = False
    variance_limit: Optional[float] = 0.01
    decay: Optional[float] = 1000
    graph: nx.Graph =  nx.Graph()
    counter_microclisters:int = 0
    
    def create_microcluster(self, x:np.ndarray):
        if self.debug:
            print('NEW MICROCLUSTER!!!!')
        new_microcluster = MicroClusters(
            id=self.counter_microclisters,
            debug=self.debug,
            mean=x, 
            type_distance=self.type_distance, 
            variance_limit= self.variance_limit,
            decay=self.decay
        )
        
        if not self.microclusters: 
            self.microclusters = [new_microcluster] 
        else:
            self.microclusters = self.microclusters + [new_microcluster]
        self.counter_microclisters += 1
        
    def remove_microcluster(self):
        delete_microclusters_ids = [mi.id for mi in self.microclusters if mi.life<=0]
        for mi_id in delete_microclusters_ids:
            if mi_id in self.graph.nodes:
                self.graph.remove_node(mi_id)
        self.microclusters = [
            mi for mi in self.microclusters if not mi.id in delete_microclusters_ids
        ]
               
    def update_microclusters(self, x:np.ndarray):   
        # First sample
        if not self.microclusters:
            self.create_microcluster(x)
        else:
            for mi in self.microclusters:
                mi.update_microcluster(x)
                
            # If no cluster was update, a new cluster is created
            if not any(mi.update for mi in self.microclusters):
                self.create_microcluster(x)
        #remove cluster by decay
        self.remove_microcluster()
                
    def get_microcluster(self, _id):
        microclusters = [mi for mi in self.microclusters if mi.id==_id]
        if microclusters:
            return [mi for mi in self.microclusters if mi.id==_id][0]
    
    def disable_microclusters(self, microclusters_ids):
        microclusters = [self.get_microcluster(mi) for mi in microclusters_ids]
        if microclusters:
            mean_density = np.mean([mi.last_density for mi in microclusters])
            delete_microclusters_ids = [
                mi.id for mi in microclusters if mi.last_density < mean_density
            ]

            for mi_id in delete_microclusters_ids:
                self.graph.remove_node(mi_id)
            return [
                mi_id 
                for mi_id in microclusters_ids 
                if not mi_id in delete_microclusters_ids
            ]
        return []
            
                
    def update_macroclusters(self):
        _mi_update = [
            mi_update for mi_update in self.microclusters]
        
        for mi_update in _mi_update:
            _mi = [mi for mi in self.microclusters if not mi.id == mi_update.id]
            for mi in _mi:
                edge = (mi_update.id,mi.id)
                if mi_update.has_intersection(mi):
                    self.graph.add_edge(*edge)
                elif mi.id in self.graph.nodes and (
                    mi_update.id in self.graph.neighbors(mi.id)
                ):
                    self.graph.remove_edge(*edge)   
        
        # Remove microculsters desactivate
        self.macroclusters = [
            self.disable_microclusters(ma) for ma in list(nx.connected_components(self.graph))
        ]
                     
    def fit(self, x_data: np.ndarray):
        if self.debug:
            print("Training...")
        lenx = len(x_data) 
        for i, x in enumerate(x_data):
            if self.debug:               
                print(f'Training {i+1} of {lenx}')
            self.update_microclusters(x)
        self.update_macroclusters()
       
    def compute_sum_nomalized_tipicalities(self, x: np.ndarray, microclusters_ids):
        microclusters = [self.get_microcluster(mi) for mi in microclusters_ids]
        sum_density = np.sum([mi.last_density for mi in microclusters])
        
        # Compute microclusters
        for mi in microclusters:
            mi.update_microcluster(x, update=False)
            #print(f"[{mi.id}] excentricidade ::: {mi.last_eccentricity}")
        
        return np.sum([
            (mi.last_normalized_tipicality/sum_density) * mi.last_density 
            for mi in microclusters]) 
#         if mi.last_normalized_tipicality else None]) 
        
    def _predict_macrocluster(self, x: np.ndarray):
        sum_nomalized_tipicalities = [
            (label, self.compute_sum_nomalized_tipicalities(x, macrocluster))
            for label, macrocluster in enumerate(self.macroclusters)
        ]
        
        _sum_nomalized_tipicalities = [x for x in sum_nomalized_tipicalities if x is not None]
        #print(f"_sum_nomalized_tipicalities ::: {_sum_nomalized_tipicalities}")
        if len(_sum_nomalized_tipicalities) == 0:
            print(_sum_nomalized_tipicalities)
        return max(
            [x for x in _sum_nomalized_tipicalities if x is not None],
            key=lambda item:item[1]
        )[0] 
    
    def predict(self, x_data: np.ndarray):
        y = []
        lenx = len(x_data) 
        for i, x in enumerate(x_data):
            if self.debug:  
                if self.debug:               
                    print(f'Testing {i+1} of {lenx}')
            label = self._predict_macrocluster(x)
            y.append(label)
        return y

stream_df = pd.read_csv("../InfoSource/std_7/std_0.csv", header=0, sep=",")
X = stream_df[['x', 'y']].values
y = stream_df['class'].values
evol_model_old_ds3 = EvolvingMicroTEDA(variance_limit=0.0007, decay=4000)
evol_model_old_ds3.fit(X)
y_hat_old_ds3 = evol_model_old_ds3.predict(X)