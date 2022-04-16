#define CATCH_CONFIG_MAIN
#include "../catch.hh"
#include <stdlib.h>

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

void update_unbiased_sigma_current(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns)
{
    if (matrix_index == 0)
    {
        *sigma_current = 0.0;
        return;
    }
    double first_fraction = (double)(matrix_index - 1.0) / (matrix_index);
    double second_fraction = (double)(matrix_index + 1.0) / (matrix_index * matrix_index);
    double dot_product = vec_dot_product(mi_current, sample_current, columns);
    *sigma_current = (first_fraction * (*sigma_current)) + (second_fraction * dot_product);
    return;
}

TEST_CASE("One dimensional recursive mean test")
{
    unsigned int rows = 14;
    unsigned int columns = 1;
    double mean = 0.0;
    double sigma = 0.0;
    double *mi_current = &mean;
    double *sigma_current = &sigma;

    double test_1d[14][1] = {{20.2}, {3.0}, {6.4}, {11.6}, {8.2}, {2.2}, {11.2}, {5.2}, {6.2}, {0.2}, {1.0}, {4.8}, {2.4}, {3.8}};
    double results[14][1] = {{0.0},
                             {147.92},
                             {82.973333},
                             {56.066667},
                             {42.932000},
                             {44.176000},
                             {37.779048},
                             {34.160000},
                             {30.477778},
                             {33.562667},
                             {33.976727},
                             {31.239697},
                             {30.047692},
                             {28.202198}};
    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_mean(mi_current, test_1d[i], i, columns);
        update_unbiased_sigma_current(sigma_current, mi_current, test_1d[i], i, columns);
        REQUIRE(fabs(*sigma_current - results[i][0]) < 0.00001);
    }
}
