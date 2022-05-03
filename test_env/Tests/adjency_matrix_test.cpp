#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

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