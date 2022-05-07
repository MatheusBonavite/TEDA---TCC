#include <stdio.h>
#include <stdlib.h>

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
    unsigned int n_micro_clusters;
    double micro_density_mean;
};

struct Micro_Cluster
{
    unsigned int number_of_data_samples;
    double *center;
    double variance;
    double eccentricity;
    double typicality;
    double density;
    double outlier_threshold_parameter;
};
void regroup_adjency_matrix(struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *adjency_matrix)
{
    return;
}