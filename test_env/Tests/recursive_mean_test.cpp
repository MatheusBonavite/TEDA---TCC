#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional recursive mean")
{
    unsigned int rows = 14;
    unsigned int columns = 1;
    double *mi_current = (double *)malloc(columns * sizeof(double));

    double test_1d[14][1] = {{20.2}, {3.0}, {6.4}, {11.6}, {8.2}, {2.2}, {11.2}, {5.2}, {6.2}, {0.2}, {1.0}, {4.8}, {2.4}, {3.8}};
    double results[14][1] = {{20.200000},
                             {11.600000},
                             {9.866667},
                             {10.300000},
                             {9.880000},
                             {8.600000},
                             {8.971429},
                             {8.500000},
                             {8.244444},
                             {7.440000},
                             {6.854545},
                             {6.683333},
                             {6.353846},
                             {6.171429}};
    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_mean(mi_current, test_1d[i], i, columns);
        REQUIRE(fabs(*mi_current - results[i][0]) < 0.00001);
    }
    free(mi_current);
}
