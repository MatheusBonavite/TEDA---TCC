#include <stdlib.h>
#include <math.h>

double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns)
{
    double *aux = (double *)malloc(columns * sizeof(double));
    double dot_product = 0.0;
    for (unsigned int j = 0; j < columns; j++)
    {
        aux[j] = fabs(vector_a[j] - vector_b[j]);
        dot_product = dot_product + (aux[j] * aux[j]);
    }
    free(aux);
    return dot_product;
}