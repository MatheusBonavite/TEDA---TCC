#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("Bfs grouping for simple graph")
{
    struct Macro_Clusters *macro_clusters_arr;
    unsigned int rows = 8;
    unsigned int columns = 8;
    unsigned int test_graph[8][8] = {
        {0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
    };
    unsigned int *matrix = int_matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns * i) + j] = test_graph[i][j];
        }
    }
    bfs_grouping(macro_clusters_arr, matrix, rows, columns);
    REQUIRE(0 == 0);
}