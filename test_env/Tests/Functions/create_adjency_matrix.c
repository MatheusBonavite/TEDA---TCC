#include <stdlib.h>
#include <stdio.h>

double two_vec_euclidean_distance(double *a, double *b, unsigned int columns);
void int_zero_matrix_initializer(unsigned int *matrix, unsigned int rows, unsigned int columns);
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
unsigned int *adjency_matrix(struct Micro_Cluster *micro_clusters_arr, unsigned int number_of_micro_clusters, unsigned int columns)
{
    double dist_centers = 0.0;
    double variance_sum = 0.0;
    unsigned int *adj_nodes = (unsigned int *)malloc((number_of_micro_clusters * number_of_micro_clusters) * sizeof(unsigned int));
    int_zero_matrix_initializer(adj_nodes, number_of_micro_clusters, number_of_micro_clusters);
    for (unsigned int i = 0; i < number_of_micro_clusters; i++)
    {
        for (unsigned int j = 0; j < number_of_micro_clusters; j++)
        {
            if (j <= i)
            {
                continue;
            }
            dist_centers = two_vec_euclidean_distance(micro_clusters_arr[i].center, micro_clusters_arr[j].center, columns);
            variance_sum = 2.0 * (micro_clusters_arr[i].variance + micro_clusters_arr[j].variance);
            unsigned int resp_condition = dist_centers < variance_sum;
            adj_nodes[(number_of_micro_clusters * i) + j] = resp_condition;
            adj_nodes[(number_of_micro_clusters * j) + i] = resp_condition;
        }
    }
    return adj_nodes;
}