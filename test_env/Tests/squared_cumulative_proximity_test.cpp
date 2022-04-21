#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional squared cumulative proximity")
{
    unsigned int rows = 3;
    unsigned int columns = 1;
    double test_1d[3][1] = {{20.0}, {12.0}, {10.0}};
    double *matrix = matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns * i) + j] = test_1d[i][j];
        }
    }
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 0, rows, columns) - 164.0) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 1, rows, columns) - 68.0) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 2, rows, columns) - 104.0) < 0.00001);
    free(matrix);
}

TEST_CASE("Two dimensional squared cumulative proximity")
{
    unsigned int rows = 7;
    unsigned int columns = 2;
    double test_2d[7][2] = {
        {20.2, 3.0}, {6.4, 11.6}, {8.2, 2.2}, {11.2, 5.2}, {6.2, 0.2}, {1.0, 4.8}, {2.4, 3.8}};
    double *matrix = matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns * i) + j] = test_2d[i][j];
        }
    }
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 0, rows, columns) - 1388.08) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 1, rows, columns) - 702.24) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 2, rows, columns) - 357.04) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 3, rows, columns) - 401.44) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 4, rows, columns) - 467.44) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 5, rows, columns) - 661.24) < 0.00001);
    REQUIRE(
        fabs(squared_cumulative_proximity(matrix, 6, rows, columns) - 540.28) < 0.00001);
    free(matrix);
}