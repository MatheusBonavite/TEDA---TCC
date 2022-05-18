#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

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

struct Micro_Cluster *p_allocate_initial_micro_cluster(unsigned int *number_of_micro_clusters, double *sample_current, unsigned int columns)
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
struct Micro_Cluster *p_update_micro_cluster(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters, double *sample_current, unsigned int k, unsigned int columns)
{
    double r_0 = 0.001;
    if ((k + 1) == 1)
    {
        return p_allocate_initial_micro_cluster(number_of_micro_clusters, sample_current, columns);
    }
    else
    {
        /* Getting the parent_id and creating a pipe! */
        int parent_id = getpid();
        int parent_to_child[2];
        int child_to_parent[2];
        if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1)
        {
            printf("An error occurred with opening the pipe!\n");
            exit(1);
        }
        /*---*/
        /* Assigning n_micro children and giving them each index */
        for (unsigned int i = 0; i < (*number_of_micro_clusters); i++)
        {
            int id;
            if (parent_id == getpid())
            {
                id = fork();
                if (id == -1)
                {
                    printf("Error while forking \n");
                    exit(1);
                }
                else if (id == 0)
                {
                    break;
                }
                else
                {
                    // Write the micro_cluster value the child will work with!
                    int write_status = write(parent_to_child[1], &i, sizeof(unsigned int));
                    if (write_status == -1)
                    {
                        printf("Error while writing \n");
                        exit(1);
                    }
                }
            }
        }
        /*---*/
        /*Working in parallel (except parent, who's waiting)*/
        if (parent_id == getpid())
        {
            unsigned int flag = 1;
            close(child_to_parent[1]); // We don't want to block this pipe, and we'll not write on it!
            read(child_to_parent[0], &flag, sizeof(unsigned int));
            while (wait(NULL) != -1 || errno != ECHILD)
            {
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
            close(parent_to_child[0]);
            close(parent_to_child[1]);
            close(child_to_parent[0]);
            return micro_clusters_arr;
        }
        else
        {
            unsigned int micro_index;
            read(parent_to_child[0], &micro_index, sizeof(unsigned int));
            unsigned int outlier = 1;
            struct Micro_Cluster temp;
            temp.number_of_data_samples = micro_clusters_arr[micro_index].number_of_data_samples;
            temp.variance = micro_clusters_arr[micro_index].variance;
            temp.eccentricity = micro_clusters_arr[micro_index].eccentricity;
            temp.center = (double *)malloc(columns * sizeof(double));
            for (unsigned int j = 0; j < columns; j++)
            {
                temp.center[j] = micro_clusters_arr[micro_index].center[j];
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

                outlier = (temp.eccentricity / 2.0) > (((squared_threshold + 1.0) / (2 * (temp.number_of_data_samples + 1.0))));
            }
            if (outlier == 0)
            {
                unsigned int flag = 0;
                /*Write to parent not to allocate a new micro_cluster*/
                write(child_to_parent[1], &flag, sizeof(unsigned int));
                /*---*/
                micro_clusters_arr[micro_index].variance = temp.variance;
                micro_clusters_arr[micro_index].eccentricity = temp.eccentricity;
                micro_clusters_arr[micro_index].number_of_data_samples = temp.number_of_data_samples + 1.0;
                for (unsigned int j = 0; j < columns; j++)
                {
                    micro_clusters_arr[micro_index].center[j] = temp.center[j];
                }
            }
            close(parent_to_child[0]);
            close(parent_to_child[1]);
            close(child_to_parent[0]);
            close(child_to_parent[1]);
            free(temp.center);
            exit(0);
        }
        /*---*/
    }
}