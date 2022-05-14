#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns)
{
    double *aux = (double *)malloc(columns * sizeof(double));
    double dot_product = 0.0;
    for (unsigned int j = 0; j < columns; j++)
    {
        aux[j] = (vector_a[j] - vector_b[j]);
        dot_product = dot_product + (aux[j] * aux[j]);
    }
    free(aux);
    return dot_product;
}

void recursive_biased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns)
{
    if (matrix_index == 0)
    {
        *sigma_current = 0.0;
        return;
    }
    double first_fraction = (double)(matrix_index) / (matrix_index + 1.0);
    double second_fraction = (double)(1.0) / (matrix_index);
    double dot_product = vec_dot_product(mi_current, sample_current, columns);
    *sigma_current = (first_fraction * (*sigma_current)) + (second_fraction * dot_product);
    return;
}

void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns)
{
    if (matrix_index == 0)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            mi_current[j] = sample_current[j];
        }
        return;
    }
    double first_fraction = (double)(matrix_index) / (matrix_index + 1.0);
    double second_fraction = (double)(1.0) / (matrix_index + 1.0);
    for (unsigned int j = 0; j < columns; j++)
    {
        mi_current[j] = (first_fraction * mi_current[j]) + (second_fraction * sample_current[j]);
    }
    return;
}

void recursive_eccentricity(
    unsigned int matrix_index,
    double *sample_current,
    double *mi_current,
    double *sigma_current,
    double *eccentricity,
    unsigned int columns)
{
    recursive_mean(mi_current, sample_current, matrix_index, columns);
    recursive_biased_sigma(sigma_current, mi_current, sample_current, matrix_index, columns);
    double dot_product = vec_dot_product(sample_current, mi_current, columns);
    double denominator = (double)(matrix_index + 1.0) * (*sigma_current);
    *eccentricity = (1.0 / (matrix_index + 1.0)) + (dot_product / denominator);
    return;
}

double two_vec_euclidean_distance(double *a, double *b, unsigned int columns)
{
    double result = 0.0;
    for (int w = 0; w < columns; w++)
    {
        result += ((a[w] - b[w]) * (a[w] - b[w]));
    }

    return (double)sqrt(result);
}

void int_zero_matrix_initializer(unsigned int *matrix, unsigned int rows, unsigned int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns * i) + j] = 0;
        }
    }
    return;
}

double empirical_m(int k)
{
    double denominator = exp(-0.007 * (k - 100.0));
    return (3.0 / (1.0 + denominator));
}

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

void adjency_matrix(struct Micro_Cluster *micro_clusters_arr, unsigned int *adj_nodes, unsigned int number_of_micro_clusters, unsigned int columns)
{
    double dist_centers = 0.0;
    double variance_sum = 0.0;
    for (unsigned int i = 0; i < number_of_micro_clusters; i++)
    {
        for (unsigned int j = 0; j < number_of_micro_clusters; j++)
        {
            if (j <= i)
            {
                continue;
            }
            dist_centers = two_vec_euclidean_distance(micro_clusters_arr[i].center, micro_clusters_arr[j].center, columns);

            if (micro_clusters_arr[i].variance > 0.0 && micro_clusters_arr[j].variance > 0.0)
            {
                variance_sum = 2.0 * (sqrt(micro_clusters_arr[i].variance) + sqrt(micro_clusters_arr[j].variance));
                unsigned int resp_condition = dist_centers < variance_sum;
                adj_nodes[(number_of_micro_clusters * i) + j] = resp_condition;
                adj_nodes[(number_of_micro_clusters * j) + i] = resp_condition;
            }
            else
            {
                if (micro_clusters_arr[i].variance > 0.0)
                {
                    double i_radius = empirical_m(micro_clusters_arr[i].number_of_data_samples) * sqrt(micro_clusters_arr[i].variance);
                    unsigned int resp_condition = dist_centers <= i_radius;
                    adj_nodes[(number_of_micro_clusters * i) + j] = resp_condition;
                    adj_nodes[(number_of_micro_clusters * j) + i] = resp_condition;
                }
                else
                {
                    double j_radius = empirical_m(micro_clusters_arr[j].number_of_data_samples) * sqrt(micro_clusters_arr[j].variance);
                    unsigned int resp_condition = dist_centers <= j_radius;
                    adj_nodes[(number_of_micro_clusters * i) + j] = resp_condition;
                    adj_nodes[(number_of_micro_clusters * j) + i] = resp_condition;
                }
            }
        }
    }
    return;
}
struct Micro_Cluster *allocate_initial_micro_cluster(unsigned int *number_of_micro_clusters, double *sample_current, unsigned int columns)
{
    struct Micro_Cluster *temp = (struct Micro_Cluster *)calloc(1, sizeof(struct Micro_Cluster));
    if (temp == NULL)
    {
        printf("Cannot allocate initial memory.\n");
        exit(1);
    }
    else
    {
        (*number_of_micro_clusters) = 1;
        temp[0].number_of_data_samples = 1;
        temp[0].center = (double *)malloc(columns * sizeof(double));
        for (unsigned int i = 0; i < columns; i++)
        {
            temp[0].center[i] = sample_current[i];
        }
        temp[0].variance = 0.0;
        return temp;
    }
}

struct Micro_Cluster *update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns)
{
    double r_0 = 0.001;
    if ((k + 1) == 1)
    {
        return allocate_initial_micro_cluster(number_of_micro_clusters, sample_current, columns);
    }
    else
    {
        unsigned int flag = 1;
        for (unsigned int i = 0; i < (*number_of_micro_clusters); i++)
        {
            unsigned int outlier = 1;
            struct Micro_Cluster temp;
            temp.number_of_data_samples = micro_clusters_arr[i].number_of_data_samples;
            temp.variance = micro_clusters_arr[i].variance;
            temp.eccentricity = micro_clusters_arr[i].eccentricity;
            temp.center = (double *)malloc(columns * sizeof(double));
            for (unsigned int j = 0; j < columns; j++)
            {
                temp.center[j] = micro_clusters_arr[i].center[j];
            }
            recursive_eccentricity(temp.number_of_data_samples, sample_current, temp.center, &temp.variance, &temp.eccentricity, columns);
            if (temp.number_of_data_samples == 1)
            {
                temp.outlier_threshold_parameter = empirical_m(2);
                double squared_threshold = temp.outlier_threshold_parameter * temp.outlier_threshold_parameter;
                int first_condition = (temp.eccentricity / 2.0) > ((squared_threshold + 1.0) / 4.0);
                int second_condition = temp.variance > r_0;
                outlier = first_condition || second_condition;
            }
            else
            {
                temp.outlier_threshold_parameter = empirical_m(temp.number_of_data_samples + 1.0);

                double squared_threshold = temp.outlier_threshold_parameter * temp.outlier_threshold_parameter;

                outlier = (temp.eccentricity / 2.0) > (((squared_threshold + 1.0) / (2.0 * (temp.number_of_data_samples + 1.0))));
            }

            if (outlier == 0)
            {
                flag = 0;
                micro_clusters_arr[i].variance = temp.variance;
                micro_clusters_arr[i].eccentricity = temp.eccentricity;
                micro_clusters_arr[i].number_of_data_samples = temp.number_of_data_samples + 1.0;
                for (unsigned int j = 0; j < columns; j++)
                {
                    micro_clusters_arr[i].center[j] = temp.center[j];
                }
            }
            free(temp.center);
        }
        if (flag == 1)
        {
            (*number_of_micro_clusters) += 1;
            struct Micro_Cluster *new_micro_arr = (struct Micro_Cluster *)realloc(micro_clusters_arr, (*number_of_micro_clusters) * sizeof(struct Micro_Cluster));
            if (new_micro_arr == NULL)
            {
                printf("Cannot allocate more memory.\n");
                exit(1);
            }
            micro_clusters_arr = new_micro_arr;
            micro_clusters_arr[(*number_of_micro_clusters) - 1].number_of_data_samples = 1;
            micro_clusters_arr[(*number_of_micro_clusters) - 1].center = (double *)malloc(columns * sizeof(double));
            for (unsigned int i = 0; i < columns; i++)
            {
                micro_clusters_arr[(*number_of_micro_clusters) - 1].center[i] = sample_current[i];
            }
            micro_clusters_arr[(*number_of_micro_clusters) - 1].variance = 0.0;
        }
    }
    return micro_clusters_arr;
}