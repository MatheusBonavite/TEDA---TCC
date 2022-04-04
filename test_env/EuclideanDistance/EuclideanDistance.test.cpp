#define CATCH_CONFIG_MAIN
#include "../catch.hh"
#include <math.h>
#include <stdlib.h>

double euclidean_distance(double **matrix, unsigned int i, unsigned int j, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int w = 0; w < amount_of_columns; w++)
    {
        result += ((matrix[i][w] - matrix[j][w]) * (matrix[i][w] - matrix[j][w]));
    }

    return (double)result;
}

void zero_matrix_initializer(double **matrix, unsigned int rows, unsigned int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = 0;
        }
    }
    return;
}

double **matrix_allocation(unsigned int rows, unsigned int columns)
{
    double **matrix = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (double *)malloc(columns * sizeof(double));
    zero_matrix_initializer(matrix, rows, columns);
    return matrix;
}

TEST_CASE("This is a test")
{

    unsigned int rows = 14;
    unsigned int columns = 1;

    double **matrix = matrix_allocation(rows, columns);

    REQUIRE(2 + 2 == 4);
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}