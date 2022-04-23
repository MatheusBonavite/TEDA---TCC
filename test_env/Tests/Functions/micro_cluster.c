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
void recursive_eccentricity(unsigned int matrix_index, double *sample_current, double *mi_current, double *sigma_current, double *eccentricity, unsigned int columns);
struct Micro_Cluster *update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns)
{
    double r_0 = 0.001;
    if ((k + 1) == 1)
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
    else
    {
        unsigned int flag = 1;
        for (unsigned int i = 0; i < (*number_of_micro_clusters); i++)
        {
            unsigned int outlier = 1;
            double *previous_mi = (double *)malloc(columns * sizeof(double));
            for (unsigned int j = 0; j < columns; j++)
            {
                previous_mi[j] = micro_clusters_arr[i].center[j];
            }
            double previous_sigma = micro_clusters_arr[i].variance;
            double previous_eccentricity = micro_clusters_arr[i].eccentricity;
            if (micro_clusters_arr[i].number_of_data_samples == 2 || (k + 1) == 2)
            {
                double *sigma_current = &micro_clusters_arr[i].variance;
                double *eccentricity = &micro_clusters_arr[i].eccentricity;
                recursive_eccentricity(k, sample_current, micro_clusters_arr[i].center, sigma_current, eccentricity, columns);
                micro_clusters_arr[i].outlier_threshold_parameter = empirical_m(micro_clusters_arr[i].number_of_data_samples);

                double squared_threshold = micro_clusters_arr[i].outlier_threshold_parameter * micro_clusters_arr[i].outlier_threshold_parameter;
                int first_condition = (micro_clusters_arr[i].eccentricity / 2.0) > ((squared_threshold + 1.0) / 4.0);
                int second_condition = micro_clusters_arr[i].variance < r_0;
                outlier = first_condition && second_condition;
                printf("Outlier ::: %u \n", outlier);
            }
            else
            {
                double *sigma_current = &micro_clusters_arr[i].variance;
                double *eccentricity = &micro_clusters_arr[i].eccentricity;
                recursive_eccentricity(k, sample_current, micro_clusters_arr[i].center, sigma_current, eccentricity, columns);
                micro_clusters_arr[i].outlier_threshold_parameter = empirical_m(micro_clusters_arr[i].number_of_data_samples);

                double squared_threshold = micro_clusters_arr[i].outlier_threshold_parameter * micro_clusters_arr[i].outlier_threshold_parameter;
                outlier = (micro_clusters_arr[i].eccentricity / 2.0) > ((squared_threshold + 1.0) / 4.0);
                printf("Outlier ::: %u \n", outlier);
            }

            if (outlier == 0)
            {
                printf("Outlier is false ::: hence micro_cluster should change \n");
                flag = 0;
            }
            else
            {
                printf("Outlier is still true ::: hence micro_cluster should remain the same \n");
                for (unsigned int j = 0; j < columns; j++)
                {
                    micro_clusters_arr[i].center[j] = previous_mi[j];
                }
                micro_clusters_arr[i].variance = previous_sigma;
                micro_clusters_arr[i].eccentricity = previous_eccentricity;
            }
            free(previous_mi);
        }
        if (flag == 1)
        {
            printf("Supposed to create a new micro cluster \n");
        }
    }
    printf("\n\n");
    return micro_clusters_arr;
}