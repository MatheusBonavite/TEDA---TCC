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
    unsigned int rows = 4;
    double test_1d[4][1] = {{20.0}, {19.99}, {12.0}, {11.99}};
    struct Micro_Cluster *micro_clusters_arr;
    unsigned int *number_of_micro_clusters = &n;
    for (unsigned int i = 0; i < rows; i++)
    {
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_1d[i], i, columns);
    }
    printf("Number of micro_clusters are :::: %u\n", *number_of_micro_clusters);
    for(unsigned int i=0; i < *number_of_micro_clusters; i++){
        printf("\n1) Micro[%u].Variance ::: %lf\n", i, micro_clusters_arr[i].variance);
        printf("\n2) Micro[%u].Eccentricity ::: %lf\n",  i, micro_clusters_arr[i].eccentricity);
        printf("\n3) Micro[%u].Center ::: \n", i);
        for(unsigned int j=0; j<columns; j++){
            printf("Micro[%u].Center ::: %lf\n", i, micro_clusters_arr[i].center[j]);
        }
        printf("===============================================================================\n");
    }
    for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
    {
        free(micro_clusters_arr[j].center);
    }
    REQUIRE(0 == 0);
}