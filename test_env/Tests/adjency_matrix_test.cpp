#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./header/global_header.h"

TEST_CASE("Adjency matrix test for 4x(1-x)")
{
    FILE *file = fopen("./plots/adjency_test.txt", "w");
    if (file == NULL)
    {
        printf("Could not fopen! \n");
        exit(1);
    }
    unsigned int problem_dimension = 2;
    unsigned int rows = 100000;
    unsigned int columns = 2;
    unsigned int n = 0;
    double *matrix = matrix_allocation(rows, columns);
    struct Micro_Cluster *micro_clusters_arr;
    unsigned int *number_of_micro_clusters = &n;

    double x0 = 0.33;
    double x1 = 0.315;
    for (unsigned int i = 0; i < rows; i++)
    {
        double *test_2d = (double *)calloc(1, columns * sizeof(double));
        x0 = 4.0 * (x0) * (1.0 - x0);
        x1 = 4.0 * (x1) * (1.0 - x1);
        test_2d[0] = x0;
        test_2d[1] = x1;
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_2d, i, columns);
        free(test_2d);
    }

    for (unsigned int i = 0; i < *number_of_micro_clusters; i++)
    {
        char *buffer;
        sprintf(buffer, "[%u]:", i);
        for (unsigned int j = 0; j < columns; j++)
        {
            sprintf(buffer, "%s {%lf}", buffer, micro_clusters_arr[i].center[j]);
        }
        sprintf(buffer, "%s (%lf)\n", buffer, micro_clusters_arr[i].variance);

        int file_i = 0;
        while (file_i < strlen(buffer))
        {
            int result = fputc(buffer[file_i], file);
            if (result == EOF)
            {
                printf("Failed to write character! \n");
                exit(1);
            }
            file_i++;
        }
    }

    unsigned int *adj_node = adjency_matrix(micro_clusters_arr, *number_of_micro_clusters, columns);
    unsigned int hits = 0;
    for (unsigned int w = 0; w < *number_of_micro_clusters; w++)
    {
        for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
        {
            if (j <= w)
            {
                continue;
            }
            if (adj_node[(w * columns) + j] == 1)
            {
                hits++;
            }
        }
    }
    printf("Amount of hits ::: %u \n", hits);
    for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
    {
        free(micro_clusters_arr[j].center);
    }
    free(adj_node);
    REQUIRE(0 == 0);
}