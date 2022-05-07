#include <stdio.h>
#include <stdlib.h>

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
    unsigned int n_micro_clusters;
    double micro_eccentricity_mean;
};

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
void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
struct Macro_Clusters *bfs_grouping(struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *adjency_matrix, unsigned int *number_of_macro_clusters, unsigned int number_of_micro_clusters)
{
    unsigned int *visited = (unsigned int *)calloc((number_of_micro_clusters), sizeof(unsigned int));
    for (unsigned int w = 0; w < number_of_micro_clusters; w++)
    {
        unsigned int start_point = w;
        if (visited[start_point] == 1)
            continue;

        unsigned int *queue = (unsigned int *)calloc((number_of_micro_clusters), sizeof(unsigned int));
        unsigned int front = 0, rear = 0;
        queue[rear] = start_point;
        visited[start_point] = 1;

        // when front > rear, means queue is empty!
        while (front <= rear)
        {
            start_point = queue[front];
            for (unsigned int i = 0; i < number_of_micro_clusters; i++)
            {
                if (adjency_matrix[(start_point * number_of_micro_clusters) + i] == 1 && visited[i] == 0)
                {
                    queue[++rear] = i;
                    visited[i] = 1;
                }
            }
            front++;
        }
        if (*number_of_macro_clusters == 0)
        {
            macro_clusters_arr = (struct Macro_Clusters *)calloc(1, sizeof(struct Macro_Clusters));
            if (macro_clusters_arr == NULL)
            {
                printf("Could not allocate memory \n");
                exit(1);
            }
        }
        else
        {
            struct Macro_Clusters *new_macro_arr = (struct Macro_Clusters *)realloc(macro_clusters_arr, (*number_of_macro_clusters + 1) * sizeof(struct Macro_Clusters));
            if (new_macro_arr == NULL)
            {
                printf("Cannot allocate more memory.\n");
                exit(1);
            }
            macro_clusters_arr = new_macro_arr;
        }
        double density_mean = 0.0;
        double *current_density_mean = &density_mean;
        macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters = (unsigned int *)calloc(rear + 1, sizeof(unsigned int));
        macro_clusters_arr[*number_of_macro_clusters].n_micro_clusters = rear + 1;

        if (macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters == NULL)
        {
            printf("Could not allocate memory \n");
            exit(1);
        }
        for (unsigned int wu = 0; wu < rear; wu++)
        {
            unsigned int micro_index = queue[wu];
            double *current_eccentricity = &(micro_clusters_arr[micro_index].eccentricity);
            macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters[wu] = micro_index;
            recursive_mean(current_density_mean, current_eccentricity, wu, 1);
        }
        double *current_eccentricity = &(micro_clusters_arr[start_point].eccentricity);
        macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters[rear] = start_point;
        recursive_mean(current_density_mean, current_eccentricity, rear, 1);
        macro_clusters_arr[*number_of_macro_clusters].micro_eccentricity_mean = *current_density_mean;
        *number_of_macro_clusters = *number_of_macro_clusters + 1;

        free(queue);
    }
    free(visited);
    return macro_clusters_arr;
}