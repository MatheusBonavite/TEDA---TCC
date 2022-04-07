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

double *online_eccentricity_s(
    double *matrix,
    unsigned int matrix_index,
    double *sample_current,
    unsigned int columns
){

    for(unsigned int j=0; j<columns; j++){
        matrix[(columns * matrix_index) + j] = sample_current[j];
    }
    double* matrix_aux = (double *) realloc(matrix, (((matrix_index+2)*columns) * sizeof(double)));
    if(matrix_aux == NULL){
        printf("Not enough memory \n");
        free(matrix);
        exit(1);
    }
    return matrix_aux;
}

TEST_CASE("One dimensional online eccentricity proximity")
{
    unsigned int rows = 4;
    unsigned int columns = 1;
    unsigned int index = 0;
    double test_1d[rows][columns] = { { 20.0 }, { 12.0 }, { 10.0 }, { 11.0 } };

    double *matrix = matrix_allocation(1, columns);
    for(unsigned int i=0; i<rows; i++){
        matrix = online_eccentricity_s(matrix, index, test_1d[i], columns);
        index++;
    }
    free(matrix);
    REQUIRE(
        0 == 0
    );
}