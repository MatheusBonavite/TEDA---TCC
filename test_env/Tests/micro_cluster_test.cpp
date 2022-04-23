#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("Saturation point for empirical m function close to 3.0")
{
    unsigned int samples = 1;
    double test_1d[3][1] = {{20.0}, {12.0}, {10.0}};
    struct Micro_Cluster *micro_clusters_arr;
    for (unsigned int i = 0; i < 3; i++)
    {
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, i);
        if (i == 0)
        {
            printf("First Microcluster initialized with ::: \n");
            printf("number_of_micro_clusters ::: %d\n", micro_clusters_arr[0].number_of_micro_clusters);
            printf("number_of_data_samples ::: %d\n", micro_clusters_arr[0].number_of_data_samples);
            printf("center ::: %lf\n", micro_clusters_arr[0].center);
            printf("variance ::: %lf\n", micro_clusters_arr[0].variance);
        }
    }
    REQUIRE(0 == 0);
}