#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("Micro cluster call")
{
    unsigned int samples = 1;
    unsigned int n = 0;
    unsigned int columns = 1;
    unsigned int rows = 3;
    double test_1d[3][1] = {{20.0}, {1.0}, {10.0}};
    struct Micro_Cluster *micro_clusters_arr;
    unsigned int *number_of_micro_clusters = &n;
    for (unsigned int i = 0; i < rows; i++)
    {
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_1d[i], i, columns);
        printf("First Microcluster ::: \n");
        printf("number_of_data_samples ::: %d\n", micro_clusters_arr[0].number_of_data_samples);
        for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
        {
            printf("center[%u] ::: %lf\n", j, micro_clusters_arr[0].center[j]);
        }
        printf("variance ::: %lf\n", micro_clusters_arr[0].variance);
    }
    for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
    {
        free(micro_clusters_arr[j].center);
    }
    REQUIRE(0 == 0);
}