#include <stdio.h>
#include <stdlib.h>

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
    unsigned int n_micro_clusters;
};

struct Macro_Clusters *bfs_grouping(struct Macro_Clusters *macro_clusters_arr, unsigned int *adjency_matrix, unsigned int *number_of_macro_clusters, unsigned int number_of_micro_clusters, unsigned int columns)
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
                if (adjency_matrix[(start_point * columns) + i] == 1 && visited[i] == 0)
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
        macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters = (unsigned int *)calloc(rear + 1, sizeof(unsigned int));
        macro_clusters_arr[*number_of_macro_clusters].n_micro_clusters = rear + 1;

        if (macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters == NULL)
        {
            printf("Could not allocate memory \n");
            exit(1);
        }
        for (unsigned int wu = 0; wu < rear; wu++)
        {
            macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters[wu] = queue[wu];
        }
        macro_clusters_arr[*number_of_macro_clusters].group_of_micro_clusters[rear] = start_point;
        *number_of_macro_clusters = *number_of_macro_clusters + 1;

        free(queue);
    }
    free(visited);
    return macro_clusters_arr;
}