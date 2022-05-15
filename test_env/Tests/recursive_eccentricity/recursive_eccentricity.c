#include <stdlib.h>
#include <math.h>
#include <stdio.h>

void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns)
{
    if (matrix_index == 0)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            mi_current[j] = sample_current[j];
        }
        return;
    }
    double first_fraction = (double)(matrix_index) / (matrix_index + 1.0);
    double second_fraction = (double)(1.0) / (matrix_index + 1.0);
    for (unsigned int j = 0; j < columns; j++)
    {
        mi_current[j] = (first_fraction * mi_current[j]) + (second_fraction * sample_current[j]);
    }
    return;
}

double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns)
{
    double *aux = (double *)malloc(columns * sizeof(double));
    double dot_product = 0.0;
    for (unsigned int j = 0; j < columns; j++)
    {
        aux[j] = (vector_a[j] - vector_b[j]);
        dot_product = dot_product + (aux[j] * aux[j]);
    }
    free(aux);
    return dot_product;
}

void recursive_biased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns)
{
    if (matrix_index == 0)
    {
        *sigma_current = 0.0;
        return;
    }
    double first_fraction = (double)(matrix_index) / (matrix_index + 1.0);
    double second_fraction = (double)(1.0) / (matrix_index);
    double dot_product = vec_dot_product(mi_current, sample_current, columns);
    *sigma_current = (first_fraction * (*sigma_current)) + (second_fraction * dot_product);
    return;
}

void recursive_eccentricity(
    unsigned int matrix_index,
    double *sample_current,
    double *mi_current,
    double *sigma_current,
    double *eccentricity,
    unsigned int columns)
{
    recursive_mean(mi_current, sample_current, matrix_index, columns);
    recursive_biased_sigma(sigma_current, mi_current, sample_current, matrix_index, columns);
    double dot_product = vec_dot_product(sample_current, mi_current, columns);
    double denominator = (double)(matrix_index + 1.0) * (*sigma_current);
    *eccentricity = (1.0 / (matrix_index + 1.0)) + (dot_product / denominator);
    return;
}