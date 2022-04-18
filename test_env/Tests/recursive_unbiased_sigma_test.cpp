#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional recursive unbiased variance")
{
    unsigned int rows = 14;
    unsigned int columns = 1;
    double mean = 0.0;
    double sigma = 0.0;
    double *mi_current = &mean;
    double *sigma_current = &sigma;

    double test_1d[14][1] = {{20.2}, {3.0}, {6.4}, {11.6}, {8.2}, {2.2}, {11.2}, {5.2}, {6.2}, {0.2}, {1.0}, {4.8}, {2.4}, {3.8}};
    double results[14][1] = {{0.0},
                             {147.92},
                             {82.973333},
                             {56.066667},
                             {42.932000},
                             {44.176000},
                             {37.779048},
                             {34.160000},
                             {30.477778},
                             {33.562667},
                             {33.976727},
                             {31.239697},
                             {30.047692},
                             {28.202198}};
    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_mean(mi_current, test_1d[i], i, columns);
        recursive_unbiased_sigma(sigma_current, mi_current, test_1d[i], i, columns);
        REQUIRE(fabs(*sigma_current - results[i][0]) < 0.00001);
    }
}
