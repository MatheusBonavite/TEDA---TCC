#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double two_vec_euclidean_distance(double *a, double *b, unsigned int columns);
void int_zero_matrix_initializer(unsigned int *matrix, unsigned int rows, unsigned int columns);
double empirical_m(int k);
struct Micro_Cluster
{
    unsigned int number_of_data_samples;
    double *center;
    double variance;
    double eccentricity;
    unsigned int active;
};
void adjency_matrix(struct Micro_Cluster *micro_clusters_arr, unsigned int *adj_nodes, unsigned int number_of_micro_clusters, unsigned int columns)
{
    for (unsigned int i = 0; i < number_of_micro_clusters; i++)
    {
        for (unsigned int j = 0; j < number_of_micro_clusters; j++)
        {
            if ((j <= i))
                continue;
            double dist_centers = two_vec_euclidean_distance(micro_clusters_arr[i].center, micro_clusters_arr[j].center, columns);
            double variance_sum = 2.0 * (sqrt(micro_clusters_arr[i].variance) + sqrt(micro_clusters_arr[j].variance));
            unsigned int resp_condition = dist_centers < variance_sum;
            adj_nodes[(number_of_micro_clusters * i) + j] = (resp_condition && micro_clusters_arr[i].active == 1);
            adj_nodes[(number_of_micro_clusters * j) + i] = (resp_condition && micro_clusters_arr[j].active == 1);
        }
    }
    return;
}