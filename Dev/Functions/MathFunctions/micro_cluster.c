#include <stdlib.h>
#include <stdio.h>

struct Micro_Cluster
{
    unsigned int number_of_data_samples;
    double *center;
    double variance;
    double eccentricity;
    unsigned int active;
};
double empirical_m(int k);
void recursive_eccentricity(unsigned int matrix_index, double *sample_current, double *mi_current, double *sigma_current, double *eccentricity, unsigned int columns);

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
        temp[0].center = (double *)calloc(columns, sizeof(double));
        for (unsigned int i = 0; i < columns; i++)
        {
            temp[0].center[i] = sample_current[i];
        }
        temp[0].variance = 0.0;
        temp[0].active = 1;
        temp[0].eccentricity = 0.0;
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
            temp.center = (double *)calloc(columns, sizeof(double));
            for (unsigned int j = 0; j < columns; j++)
            {
                temp.center[j] = micro_clusters_arr[i].center[j];
            }
            recursive_eccentricity(temp.number_of_data_samples + 1.0, sample_current, temp.center, &temp.variance, &temp.eccentricity, columns);
            if (temp.number_of_data_samples == 1)
            {
                double empirical_m_value = empirical_m(2);
                double squared_threshold = empirical_m_value * empirical_m_value;
                int first_condition = (temp.eccentricity / 2.0) > ((squared_threshold + 1.0) / 4.0);
                int second_condition = temp.variance > r_0;
                outlier = first_condition || second_condition;
            }
            else
            {
                double empirical_m_value = empirical_m(temp.number_of_data_samples + 1.0);

                double squared_threshold = empirical_m_value * empirical_m_value;

                outlier = (temp.eccentricity / 2.0) > ((squared_threshold + 1.0) / (2.0 * (temp.number_of_data_samples + 1.0)));
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
            micro_clusters_arr[(*number_of_micro_clusters) - 1].center = (double *)calloc(columns, sizeof(double));
            for (unsigned int i = 0; i < columns; i++)
            {
                micro_clusters_arr[(*number_of_micro_clusters) - 1].center[i] = sample_current[i];
            }
            micro_clusters_arr[(*number_of_micro_clusters) - 1].active = 1;
            micro_clusters_arr[(*number_of_micro_clusters) - 1].variance = 0.0;
            micro_clusters_arr[(*number_of_micro_clusters) - 1].eccentricity = 0.0;
        }
    }
    return micro_clusters_arr;
}