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

double empirical_m(int k);
double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns);
void recursive_biased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_eccentricity(unsigned int matrix_index, double *sample_current, double *mi_current, double *sigma_current, double *eccentricity, unsigned int columns);
struct Micro_Cluster *allocate_initial_micro_cluster(unsigned int *number_of_micro_clusters, double *sample_current, unsigned int columns);
struct Micro_Cluster *update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns);