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
struct Micro_Cluster *update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int k);
struct Micro_Cluster
{
    int number_of_micro_clusters;
    int number_of_data_samples;
    double center;
    double variance;
    double eccentricity;
    double typicality;
    double density;
    double outlier_threshold;
};