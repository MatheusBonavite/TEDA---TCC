#include <stdlib.h>
#include <stdio.h>

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

double two_vec_euclidean_distance(double *a, double *b, unsigned int columns);
void int_zero_matrix_initializer(unsigned int *matrix, unsigned int rows, unsigned int columns);
double empirical_m(int k);
void adjency_matrix(struct Micro_Cluster *micro_clusters_arr, unsigned int *adj_nodes, unsigned int number_of_micro_clusters, unsigned int columns);
double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns);
struct Micro_Cluster *allocate_initial_micro_cluster(unsigned int *number_of_micro_clusters, double *sample_current, unsigned int columns);
void recursive_biased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_eccentricity(
    unsigned int matrix_index,
    double *sample_current,
    double *mi_current,
    double *sigma_current,
    double *eccentricity,
    unsigned int columns);
double two_vec_euclidean_distance(double *a, double *b, unsigned int columns);
struct Micro_Cluster *update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns);
struct Macro_Clusters *bfs_grouping(struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *adjency_matrix, unsigned int *number_of_macro_clusters, unsigned int number_of_micro_clusters);

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
    unsigned int n_micro_clusters;
    double micro_density_mean;
};