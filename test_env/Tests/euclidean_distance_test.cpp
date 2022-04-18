#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("One dimensional euclidean distance")
{
    unsigned int problem_dimension = 1;
    unsigned int rows = 14;
    unsigned int columns = 1;
    double test_1d[14][1] = {
        {20.2},
        {3.0},
        {6.4},
        {11.6},
        {8.2},
        {2.2},
        {11.2},
        {5.2},
        {6.2},
        {0.2},
        {1.0},
        {4.8},
        {2.4},
        {3.8}};
    double *matrix = matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(i * columns) + j] = test_1d[i][j];
        }
    }
    REQUIRE(
        fabs(euclidean_distance(matrix, 0, 1, problem_dimension) - 17.2) < 0.00001);
    REQUIRE(
        fabs(euclidean_distance(matrix, 0, 2, problem_dimension) - 13.8) < 0.00001);
    REQUIRE(
        fabs(euclidean_distance(matrix, 5, 10, problem_dimension) - 1.2) < 0.00001);
    REQUIRE(
        fabs(euclidean_distance(matrix, 3, 13, problem_dimension) - 7.8) < 0.00001);
    free(matrix);
}

TEST_CASE("Two dimensional euclidean distance")
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
        fabs(euclidean_distance(matrix, 0, 1, problem_dimension) - 16.260381) < 0.00001);
    REQUIRE(
        fabs(euclidean_distance(matrix, 2, 6, problem_dimension) - 6.016644) < 0.00001);
    free(matrix);
}

TEST_CASE("Three dimensional euclidean distance")
{
    unsigned int problem_dimension = 3;
    unsigned int rows = 4;
    unsigned int columns = 3;
    double test_3d[4][3] = {
        {20.2, 3.0, 6.4}, {11.6, 8.2, 2.2}, {11.2, 5.2, 6.2}, {0.2, 1.0, 4.8}};
    double *matrix = matrix_allocation(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(i * columns) + j] = test_3d[i][j];
        }
    }
    REQUIRE(
        fabs(euclidean_distance(matrix, 0, 1, problem_dimension) - 10.892199) < 0.00001);
    free(matrix);
}