#define CATCH_CONFIG_MAIN
#include "../catch.hh"
#include <math.h>
#include <stdlib.h>

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

void dealloc_matrix(double **matrix, unsigned int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

double euclidean_distance(double **matrix, unsigned int i, unsigned int j, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int w = 0; w < amount_of_columns; w++)
    {
        result += ((matrix[i][w] - matrix[j][w]) * (matrix[i][w] - matrix[j][w]));
    }

    return (double) sqrt(result);
}

double squared_euclidean_distance(double **matrix, unsigned int i, unsigned int j, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int w = 0; w < amount_of_columns; w++)
    {
        result += ((matrix[i][w] - matrix[j][w]) * (matrix[i][w] - matrix[j][w]));
    }

    return (double) result;
}

TEST_CASE("One dimensional euclidean distance")
{

    unsigned int rows = 14;
    unsigned int columns = 1;
    double test_1d[] = {
        20.2, 3.0, 6.4, 11.6, 8.2, 2.2, 11.2, 5.2, 6.2, 0.2, 1.0, 4.8, 2.4, 3.8
    };
    double **matrix = matrix_allocation(rows, columns);
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix[i][j] = test_1d[i];
        }
    }
    REQUIRE(
        euclidean_distance(matrix, 0, 1, 1) == 17.2
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("One dimensional squared euclidean distance")
{
    unsigned int rows = 14;
    unsigned int columns = 1;
    double test_1d[] = {
        20.2, 3.0, 6.4, 11.6, 8.2, 2.2, 11.2, 5.2, 6.2, 0.2, 1.0, 4.8, 2.4, 3.8
    };
    double **matrix = matrix_allocation(rows, columns);
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix[i][j] = test_1d[i];
        }
    }
    REQUIRE(
        squared_euclidean_distance(matrix, 0, 1, 1) == 295.84
    );
    dealloc_matrix(matrix, rows);
}