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

double cumulative_proximity(double **matrix, unsigned int i, unsigned int amount_of_rows, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int j = 0; j < amount_of_rows; j++)
    {
        result += euclidean_distance(matrix, i, j, amount_of_columns);
    }
    return result;
}

TEST_CASE("One dimensional cumulative proximity")
{
    unsigned int rows = 3;
    unsigned int columns = 1;
    double test_1d[] = { 20.0, 12.0, 10.0 };
    double **matrix = matrix_allocation(rows, columns);
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix[i][j] = test_1d[i];
        }
    }
    REQUIRE(
        fabs(cumulative_proximity(matrix, 0, rows, columns) - 18.0) < 0.00001
    );
    REQUIRE(
        fabs(cumulative_proximity(matrix, 1, rows, columns) - 10.0) < 0.00001
    );
    REQUIRE(
        fabs(cumulative_proximity(matrix, 2, rows, columns) - 12.0) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("Two dimensional cumulative proximity")
{
    unsigned int rows = 7;
    unsigned int columns = 2;
    double test_2d[7][2] = {
        {20.2, 3.0}, {6.4, 11.6}, {8.2, 2.2}, {11.2, 5.2}, {6.2, 0.2}, {1.0, 4.8}, {2.4, 3.8}
    };
    double **matrix = matrix_allocation(rows, columns);
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix[i][j] = test_2d[i][j];
        }
    }
    REQUIRE(
        fabs(cumulative_proximity(matrix, 0, rows, columns) - 88.931419) < 0.00001
    );
    REQUIRE(
        fabs(cumulative_proximity(matrix, 2, rows, columns) - 42.340202) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("Three dimensional cumulative proximity")
{
    unsigned int rows = 4;
    unsigned int columns = 3;
    double test_2d[7][3] = {
        {20.2, 3.0, 6.4}, {11.6, 8.2, 2.2}, {11.2, 5.2, 6.2}, {0.2, 1.0, 4.8}
    };
    double **matrix = matrix_allocation(rows, columns);
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix[i][j] = test_2d[i][j];
        }
    }
    REQUIRE(
        fabs(cumulative_proximity(matrix, 1, rows, columns) - 29.639888) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}