#include <stdio.h>
#include <stdlib.h>

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
    unsigned int n_micro_clusters;
    double micro_density_mean;
    unsigned int active;
};

struct Micro_Cluster
{
    unsigned int number_of_data_samples;
    double *center;
    double variance;
    double eccentricity;
    unsigned int active;
    double life;
};

void regroup_adjency_matrix(struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *adjency_matrix, unsigned int n_macro_clusters, unsigned int n_micro_clusters)
{

    for (unsigned int i = 0; i < n_macro_clusters; i++)
    {
        for (unsigned int j = 0; j < macro_clusters_arr[i].n_micro_clusters; j++)
        {
            unsigned int micro_index = macro_clusters_arr[i].group_of_micro_clusters[j];
            double micro_density = (2.0 / micro_clusters_arr[micro_index].eccentricity);
            if (micro_density < macro_clusters_arr[i].micro_density_mean)
                micro_clusters_arr[micro_index].active = 1;
        }
    }

    return;
}
