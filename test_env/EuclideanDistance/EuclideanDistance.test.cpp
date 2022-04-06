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
    unsigned int problem_dimension = 1;
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
        fabs(euclidean_distance(matrix, 0, 1, problem_dimension) - 17.2) < 0.00001
    );
    REQUIRE(
        fabs(euclidean_distance(matrix, 0, 2, problem_dimension) - 13.8) < 0.00001
    );
    REQUIRE(
        fabs(euclidean_distance(matrix, 5, 10, problem_dimension) - 1.2) < 0.00001
    );
    REQUIRE(
        fabs(euclidean_distance(matrix, 3, 13, problem_dimension) - 7.8) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("Two dimensional euclidean distance")
{
    unsigned int problem_dimension = 2;
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
        fabs(euclidean_distance(matrix, 0, 1, problem_dimension) - 16.260381) < 0.00001
    );
    REQUIRE(
        fabs(euclidean_distance(matrix, 2, 6, problem_dimension) - 6.016644) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("Three dimensional euclidean distance")
{
    unsigned int problem_dimension = 3;
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
        fabs(euclidean_distance(matrix, 0, 1, problem_dimension) - 10.892199) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("One dimensional squared euclidean distance")
{
    unsigned int problem_dimension = 1;
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
        fabs(squared_euclidean_distance(matrix, 0, 1, problem_dimension) -  295.84) < 0.00001
    );
    REQUIRE(
        fabs(squared_euclidean_distance(matrix, 0, 2, problem_dimension) -  190.44) < 0.00001
    );
    REQUIRE(
        fabs(squared_euclidean_distance(matrix, 5, 10, problem_dimension) - 1.44) < 0.00001
    );
    REQUIRE(
        fabs(squared_euclidean_distance(matrix, 3, 13, problem_dimension) - 60.84) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("Two dimensional squared euclidean distance")
{
    unsigned int problem_dimension = 2;
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
        fabs(squared_euclidean_distance(matrix, 0, 1, problem_dimension) - 264.39999026516097) < 0.00001
    );
    REQUIRE(
        fabs(squared_euclidean_distance(matrix, 2, 6, problem_dimension) - 36.200005022736) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}

TEST_CASE("Three dimensional squared euclidean distance")
{
    unsigned int problem_dimension = 3;
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
        fabs(squared_euclidean_distance(matrix, 0, 1, problem_dimension) - 118.639999055601) < 0.00001
    );
    dealloc_matrix(matrix, rows);
}
