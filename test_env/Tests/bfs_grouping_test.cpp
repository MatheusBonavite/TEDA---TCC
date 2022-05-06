#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("Bfs grouping for simple graph")
{
    struct Macro_Clusters *macro_clusters_arr;
    unsigned int n = 0;
    unsigned int *number_of_macro_clusters = &n;
    unsigned int rows = 8;
    unsigned int columns = 8;
    unsigned int test_graph[8][8] = {
        {0, 1, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };
    unsigned int *matrix = int_matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns * i) + j] = test_graph[i][j];
        }
    }
    macro_clusters_arr = bfs_grouping(macro_clusters_arr, matrix, number_of_macro_clusters, rows);
    printf("\n\n\n");
    for (unsigned int i = 0; i < *number_of_macro_clusters; i++)
    {
        printf("Macro_cluster::: %u \n Group: \n", i);
        unsigned int size = macro_clusters_arr[i].n_micro_clusters;
        printf("SIZE ::: %u \n", size);
        for (unsigned int j = 0; j < size; j++)
        {
            printf("%u\n", macro_clusters_arr[i].group_of_micro_clusters[j]);
        }
    }
    for (unsigned int i = 0; i < *number_of_macro_clusters; i++)
    {
        free(macro_clusters_arr[i].group_of_micro_clusters);
    }
    free(macro_clusters_arr);
    REQUIRE(0 == 0);
}