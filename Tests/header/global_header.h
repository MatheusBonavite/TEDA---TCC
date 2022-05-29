#pragma once

struct Micro_Cluster
{
    unsigned int number_of_data_samples;
    double *center;
    double variance;
    double eccentricity;
    unsigned int active;
    double life;
};

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
    unsigned int n_micro_clusters;
    double micro_density_mean;
    unsigned int active;
};

/*MathFunctions Folder*/
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
struct Micro_Cluster *update_micro_cluster_guarded(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns, double variance_limit, double decay_value);
void adjency_matrix(struct Micro_Cluster *micro_clusters_arr, unsigned int *adj_nodes, unsigned int number_of_micro_clusters, unsigned int columns);
struct Macro_Clusters *bfs_grouping(struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *adjency_matrix, unsigned int *number_of_macro_clusters, unsigned int number_of_micro_clusters, unsigned int disconsider_unitary_macro);
unsigned int *int_matrix_allocation(unsigned int rows, unsigned int columns);
void regroup_adjency_matrix(struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *adjency_matrix, unsigned int n_macro_clusters, unsigned int n_micro_clusters);
struct Micro_Cluster *p_update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns);
void recursive_eccentricity_guarded(
    unsigned int matrix_index,
    double *sample_current,
    double *mi_current,
    double *sigma_current,
    double *eccentricity,
    unsigned int columns,
    double variance_limit);