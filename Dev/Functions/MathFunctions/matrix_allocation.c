#include <stdlib.h>
void zero_matrix_initializer(double *matrix, unsigned int rows, unsigned int columns);
void int_zero_matrix_initializer(unsigned int *matrix, unsigned int rows, unsigned int columns);

double *matrix_allocation(unsigned int rows, unsigned int columns)
{
    double *matrix = (double *)malloc((rows * columns) * sizeof(double));
    zero_matrix_initializer(matrix, rows, columns);
    return matrix;
}

unsigned int *int_matrix_allocation(unsigned int rows, unsigned int columns)
{
    unsigned int *matrix = (unsigned int *)malloc((rows * columns) * sizeof(unsigned int));
    int_zero_matrix_initializer(matrix, rows, columns);
    return matrix;
}