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
void regroup_adjency_matrix(struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *adjency_matrix, unsigned int n_macro_clusters, unsigned int n_micro_clusters)
{
    unsigned int cluster_to_exclude_index = 0;
    unsigned int *clusters_to_exclude = (unsigned int *)calloc(1, sizeof(unsigned int));
    if (clusters_to_exclude == NULL)
    {
        printf("Can't allocate memory \n");
        exit(1);
    }
    for (unsigned int i = 0; i < n_macro_clusters; i++)
    {
        for (unsigned int j = 0; j < macro_clusters_arr[i].n_micro_clusters; j++)
        {
            double activation_criteria = (double)2.0 / micro_clusters_arr[macro_clusters_arr[i].group_of_micro_clusters[j]].eccentricity;
            if (activation_criteria >= macro_clusters_arr[i].micro_density_mean)
            {
            }
            else
            {
                clusters_to_exclude[cluster_to_exclude_index] = macro_clusters_arr[i].group_of_micro_clusters[j];
                printf("to exclude ::: %u \n", clusters_to_exclude[cluster_to_exclude_index]);
                cluster_to_exclude_index++;
                unsigned int *new_clusters_to_exclude = (unsigned int *)realloc(clusters_to_exclude, (cluster_to_exclude_index + 1) * sizeof(unsigned int));
                if (new_clusters_to_exclude == NULL)
                {
                    printf("Can't allocate memory \n");
                    exit(1);
                }
                clusters_to_exclude = new_clusters_to_exclude;
            }
        }
    }
    if (cluster_to_exclude_index > 0)
    {
        for (unsigned int i = 0; i < cluster_to_exclude_index; i++)
        {
            unsigned int to_exclude = clusters_to_exclude[i];
            for (unsigned int j = 0; j < n_micro_clusters; j++)
            {
                adjency_matrix[(j * n_micro_clusters) + to_exclude] = 0;
                adjency_matrix[(to_exclude * n_micro_clusters) + j] = 0;
            }
        }
    }
    free(clusters_to_exclude);
    return;
}
