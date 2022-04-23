#include <stdlib.h>
#include <stdio.h>

struct Micro_Cluster
{
    unsigned int number_of_data_samples;
    double center;
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
            temp[0].center = 1.0;
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
            double previous_mi = micro_clusters_arr[i].center;
            double previous_sigma = micro_clusters_arr[i].variance;
            double previous_eccentricity = micro_clusters_arr[i].eccentricity;
            if (micro_clusters_arr[i].number_of_data_samples == 2 || (k + 1) == 2)
            {
                double *mi_current = &micro_clusters_arr[i].center;
                double *sigma_current = &micro_clusters_arr[i].variance;
                double *eccentricity = &micro_clusters_arr[i].eccentricity;
                recursive_eccentricity(k, sample_current, mi_current, sigma_current, eccentricity, columns);
                micro_clusters_arr[i].outlier_threshold_parameter = empirical_m(micro_clusters_arr[i].number_of_data_samples);

                double squared_threshold = micro_clusters_arr[i].outlier_threshold_parameter * micro_clusters_arr[i].outlier_threshold_parameter;
                int first_condition = (micro_clusters_arr[i].eccentricity / 2.0) > ((squared_threshold + 1.0) / 4.0);
                int second_condition = micro_clusters_arr[i].variance < r_0;
                if (first_condition && second_condition)
                {
                    outlier = 1;
                }
                else
                {
                    outlier = 0;
                }
            }
            else
            {
                double *mi_current = &micro_clusters_arr[i].center;
                double *sigma_current = &micro_clusters_arr[i].variance;
                double *eccentricity = &micro_clusters_arr[i].eccentricity;
                recursive_eccentricity(k, sample_current, mi_current, sigma_current, eccentricity, columns);
                micro_clusters_arr[i].outlier_threshold_parameter = empirical_m(micro_clusters_arr[i].number_of_data_samples);

                double squared_threshold = micro_clusters_arr[i].outlier_threshold_parameter * micro_clusters_arr[i].outlier_threshold_parameter;
                int first_condition = (micro_clusters_arr[i].eccentricity / 2.0) > ((squared_threshold + 1.0) / 4.0);
                if (first_condition)
                {
                    outlier = 1;
                }
                else
                {
                    outlier = 0;
                }
            }

            if (outlier == 0)
            {
                printf("Flag is false ::: hence micro_cluster should change \n");
                flag = 0;
            }
            else
            {
                printf("Flag is still true ::: hence micro_cluster should remain the same \n");
                micro_clusters_arr[i].center = previous_mi;
                micro_clusters_arr[i].variance = previous_sigma;
                micro_clusters_arr[i].eccentricity = previous_eccentricity;
            }
        }
        if (flag == 1)
        {
            printf("Supposed to create a new micro cluster \n");
        }
    }
    return micro_clusters_arr;
}