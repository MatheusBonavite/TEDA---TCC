#pragma once
double cumulative_proximity(double *matrix, unsigned int i, unsigned int rows, unsigned int columns);
double squared_cumulative_proximity(double *matrix, unsigned int i, unsigned int rows, unsigned int columns);
void zero_matrix_initializer(double *matrix, unsigned int rows, unsigned int columns);
double eccentricity(double *matrix, unsigned int i, unsigned int amount_of_rows, unsigned int amount_of_columns);
double squared_eccentricity(double *matrix, unsigned int i, unsigned int amount_of_rows, unsigned int amount_of_columns);
double euclidean_distance(double *matrix, unsigned int i, unsigned int j, unsigned int columns);
double *matrix_allocation(unsigned int rows, unsigned int columns);
double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns);
double squared_euclidean_distance(double *matrix, unsigned int i, unsigned int j, unsigned int columns);
void recursive_unbiased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_biased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_eccentricity(unsigned int matrix_index, double *sample_current, double *mi_current, double *sigma_current, double *eccentricity, unsigned int columns);
double empirical_m(int k);
double two_vec_euclidean_distance(double *a, double *b, unsigned int columns);
void int_zero_matrix_initializer(unsigned int *matrix, unsigned int rows, unsigned int columns);
struct Micro_Cluster *update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns);
unsigned int *adjency_matrix(struct Micro_Cluster *micro_clusters_arr, unsigned int number_of_micro_clusters, unsigned int columns);
unsigned int bfs_grouping(struct Macro_Clusters *macro_clusters_arr, unsigned int *adjency_matrix, unsigned int number_of_micro_clusters, unsigned int columns);
unsigned int *int_matrix_allocation(unsigned int rows, unsigned int columns);
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

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
};