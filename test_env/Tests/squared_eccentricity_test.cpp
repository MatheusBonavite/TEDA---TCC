#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("Two dimensional offline squared eccentricity")
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
        fabs(squared_eccentricity(matrix, 0, rows, columns) - 0.6144992208528121) < 0.00001);
    REQUIRE(
        fabs(squared_eccentricity(matrix, 1, rows, columns) - 0.31087972800679986) < 0.00001);
    REQUIRE(
        fabs(squared_eccentricity(matrix, 2, rows, columns) - 0.15806063181753793) < 0.00001);
    REQUIRE(
        fabs(squared_eccentricity(matrix, 3, rows, columns) - 0.17771639042357276) < 0.00001);
    REQUIRE(
        fabs(squared_eccentricity(matrix, 4, rows, columns) - 0.20693440997308404) < 0.00001);
    REQUIRE(
        fabs(squared_eccentricity(matrix, 5, rows, columns) - 0.29272914010483075) < 0.00001);
    REQUIRE(
        fabs(squared_eccentricity(matrix, 6, rows, columns) - 0.2391804788213628) < 0.00001);
    free(matrix);
}