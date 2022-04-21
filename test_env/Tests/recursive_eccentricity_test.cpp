#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional online eccentricity")
{
    unsigned int rows = 4;
    unsigned int columns = 1;
    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double test_1d[4][1] = {{20.0}, {12.0}, {10.0}, {17.0}};
    double *mi_current = (double *)malloc(columns * sizeof(double));
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;

    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_eccentricity(i, test_1d[i], mi_current, sigma_current, eccentricity, columns);
    }
    free(mi_current);
    REQUIRE(
        0 == 0);
}