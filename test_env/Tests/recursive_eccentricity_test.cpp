#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional online eccentricity")
{
    unsigned int rows = 3;
    unsigned int columns = 1;
    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double test_1d[3][1] = {{20.0}, {12.0}, {10.0}};
    double *mi_current = (double *)malloc(columns * sizeof(double));
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;

    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_eccentricity(i, test_1d[i], mi_current, sigma_current, eccentricity, columns);
    }

    REQUIRE(fabs(*eccentricity - 0.6190476190476191) < 0.00001);
    free(mi_current);
}

TEST_CASE("Two dimensional online eccentricity")
{
    unsigned int rows = 7;
    unsigned int columns = 2;
    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double test_2d[7][2] = {
        {20.2, 3.0}, {6.4, 11.6}, {8.2, 2.2}, {11.2, 5.2}, {6.2, 0.2}, {1.0, 4.8}, {2.4, 3.8}};
    double *mi_current = (double *)malloc(columns * sizeof(double));
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;

    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_eccentricity(i, test_2d[i], mi_current, sigma_current, eccentricity, columns);
    }

    REQUIRE(fabs(*eccentricity - 0.2391804788213628) < 0.00001);
    free(mi_current);
}