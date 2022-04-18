#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional recursive biased variance test")
{
    unsigned int rows = 14;
    unsigned int columns = 1;
    double mean = 0.0;
    double sigma = 0.0;
    double *mi_current = &mean;
    double *sigma_current = &sigma;

    double test_1d[14][1] = {{20.2}, {3.0}, {6.4}, {11.6}, {8.2}, {2.2}, {11.2}, {5.2}, {6.2}, {0.2}, {1.0}, {4.8}, {2.4}, {3.8}};
    double results[14][1] = {{0.0},
                             {73.96},
                             {55.3155555556},
                             {42.05},
                             {34.3456},
                             {36.8133333333},
                             {32.3820408163},
                             {29.89},
                             {27.0913580247},
                             {30.2064},
                             {30.8879338843},
                             {28.6363888889},
                             {27.7363313609},
                             {26.187755102}};
    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_mean(mi_current, test_1d[i], i, columns);
        recursive_biased_sigma(sigma_current, mi_current, test_1d[i], i, columns);
        REQUIRE(fabs(*sigma_current - results[i][0]) < 0.00001);
    }
}
