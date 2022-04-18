#include <stdlib.h>
void zero_matrix_initializer(double *matrix, unsigned int rows, unsigned int columns);
double *matrix_allocation(unsigned int rows, unsigned int columns)
{
    double *matrix = (double *)malloc((rows * columns) * sizeof(double));
    zero_matrix_initializer(matrix, rows, columns);
    return matrix;
}