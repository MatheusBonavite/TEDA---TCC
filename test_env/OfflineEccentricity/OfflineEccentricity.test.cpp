#define CATCH_CONFIG_MAIN
#include "../catch.hh"
#include <math.h>
#include <stdlib.h>

void zero_matrix_initializer(double *matrix, unsigned int rows, unsigned int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns*i)+j] = 0;
        }
    }
    return;
}

double *matrix_allocation(unsigned int rows, unsigned int columns)
{
    double *matrix = (double *)malloc((rows*columns) * sizeof(double));
    zero_matrix_initializer(matrix, rows, columns);
    return matrix;
}

double euclidean_distance(double *matrix, unsigned int i, unsigned int j, unsigned int columns)
{
    double result = 0.0;
    for (int w = 0; w < columns; w++)
    {
        result += ((matrix[(i*columns) + w] - matrix[(j*columns) + w]) * (matrix[(i*columns) + w] - matrix[(j*columns) + w]));
    }

    return (double) sqrt(result);
}

double cumulative_proximity(double *matrix, unsigned int i, unsigned int rows, unsigned int columns)
{
    double result = 0.0;
    for (int j = 0; j < rows; j++)
    {
        result += euclidean_distance(matrix, i, j, columns);
    }
    return result;
}

double offline_eccentricity(double *matrix,  unsigned int i, unsigned int amount_of_rows, unsigned int amount_of_columns)
{
    double denominator_result = 0.0;
    for (unsigned int j = 0; j < amount_of_rows; j++)
        denominator_result += cumulative_proximity(matrix, j, amount_of_rows, amount_of_columns);
    if (denominator_result > 0.0)
        return ((2.0 * (cumulative_proximity(matrix, i, amount_of_rows, amount_of_columns))) / denominator_result);
    return INFINITY;
}

TEST_CASE("One dimensional offline eccentricity proximity")
{
    unsigned int rows = 4;
    unsigned int columns = 1;
    double test_1d[rows][columns] = { { 20.0 }, { 12.0 }, { 10.0 }, { 17.0 } };
    double *matrix = matrix_allocation(rows, columns);
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix[(i*columns) + j] = test_1d[i][j];
        }
    }
    REQUIRE(
        fabs(offline_eccentricity(matrix, 0, rows, columns) - 0.6) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 1, rows, columns) - 0.428571429) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 2, rows, columns) - 0.542857143) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 3, rows, columns) - 0.428571429) < 0.00001
    );
    free(matrix);
}

TEST_CASE("Two dimensional offline eccentricity proximity")
{
    unsigned int problem_dimension = 2;
    unsigned int rows = 7;
    unsigned int columns = 2;
    double test_2d[7][2] = {
        {20.2, 3.0}, {6.4, 11.6}, {8.2, 2.2}, {11.2, 5.2}, {6.2, 0.2}, {1.0, 4.8}, {2.4, 3.8}
    };
    double *matrix = matrix_allocation(rows, columns);
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix[(i*columns) + j] = test_2d[i][j];
        }
    }
    REQUIRE(
        fabs(offline_eccentricity(matrix, 0, rows, columns) - 0.45330834422392696) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 1, rows, columns) - 0.31950813368383457) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 2, rows, columns) - 0.21581986522363483) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 3, rows, columns) - 0.24312600952267732) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 4, rows, columns) - 0.2434238028153520) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 5, rows, columns) - 0.2777686179656019) < 0.00001
    );
    REQUIRE(
        fabs(offline_eccentricity(matrix, 6, rows, columns) - 0.24704522656497224) < 0.00001
    );
    free(matrix);
}