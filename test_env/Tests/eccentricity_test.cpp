#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional offline eccentricity")
{
    unsigned int rows = 4;
    unsigned int columns = 1;
    double test_1d[4][1] = {{20.0}, {12.0}, {10.0}, {17.0}};
    double *matrix = matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(i * columns) + j] = test_1d[i][j];
        }
    }
    REQUIRE(
        fabs(eccentricity(matrix, 0, rows, columns) - 0.6) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 1, rows, columns) - 0.428571429) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 2, rows, columns) - 0.542857143) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 3, rows, columns) - 0.428571429) < 0.00001);
    free(matrix);
}

TEST_CASE("Two dimensional offline eccentricity")
{
    unsigned int problem_dimension = 2;
    unsigned int rows = 7;
    unsigned int columns = 2;
    double test_2d[7][2] = {
        {20.2, 3.0}, {6.4, 11.6}, {8.2, 2.2}, {11.2, 5.2}, {6.2, 0.2}, {1.0, 4.8}, {2.4, 3.8}};
    double *matrix = matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(i * columns) + j] = test_2d[i][j];
        }
    }
    REQUIRE(
        fabs(eccentricity(matrix, 0, rows, columns) - 0.45330834422392696) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 1, rows, columns) - 0.31950813368383457) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 2, rows, columns) - 0.21581986522363483) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 3, rows, columns) - 0.24312600952267732) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 4, rows, columns) - 0.2434238028153520) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 5, rows, columns) - 0.2777686179656019) < 0.00001);
    REQUIRE(
        fabs(eccentricity(matrix, 6, rows, columns) - 0.24704522656497224) < 0.00001);
    free(matrix);
}