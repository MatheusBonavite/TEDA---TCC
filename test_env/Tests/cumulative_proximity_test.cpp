#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional cumulative proximity")
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
        fabs(cumulative_proximity(matrix, 0, rows, columns) - 18.0) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 1, rows, columns) - 10.0) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 2, rows, columns) - 12.0) < 0.00001);
    free(matrix);
}

TEST_CASE("Two dimensional cumulative proximity")
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
        fabs(cumulative_proximity(matrix, 0, rows, columns) - 88.931419) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 1, rows, columns) - 62.682084) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 2, rows, columns) - 42.340202) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 3, rows, columns) - 47.697205) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 4, rows, columns) - 47.755627) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 5, rows, columns) - 54.493498) < 0.00001);
    REQUIRE(
        fabs(cumulative_proximity(matrix, 6, rows, columns) - 48.466089) < 0.00001);
    free(matrix);
}

TEST_CASE("Three dimensional cumulative proximity")
{
    unsigned int rows = 4;
    unsigned int columns = 3;
    double test_2d[4][3] = {
        {20.2, 3.0, 6.4}, {11.6, 8.2, 2.2}, {11.2, 5.2, 6.2}, {0.2, 1.0, 4.8}};
    double *matrix = matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns * i) + j] = test_2d[i][j];
        }
    }
    REQUIRE(
        fabs(cumulative_proximity(matrix, 1, rows, columns) - 29.639888) < 0.00001);
    free(matrix);
}