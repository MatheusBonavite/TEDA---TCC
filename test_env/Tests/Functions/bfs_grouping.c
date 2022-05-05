#include <stdio.h>
#include <stdlib.h>

struct Macro_Clusters
{
    unsigned int *group_of_micro_clusters;
};

unsigned int bfs_grouping(struct Macro_Clusters *macro_clusters_arr, unsigned int *adjency_matrix, unsigned int number_of_micro_clusters, unsigned int columns)
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
            printf("Point : %u \n", start_point);

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
        printf("Group here the macro-cluster!\n");
        for (unsigned int wu = 0; wu < rear; wu++)
        {
            printf("%u\n", queue[wu]);
        }
        printf("%u\n", start_point);
        printf("\n");
        printf("\n\n\n");
        free(queue);
    }
    free(visited);
    return 0;
}