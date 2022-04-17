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
            matrix[(columns * i) + j] = 0;
        }
    }
    return;
}

double *matrix_allocation(unsigned int rows, unsigned int columns)
{
    double *matrix = (double *)malloc((rows * columns) * sizeof(double));
    zero_matrix_initializer(matrix, rows, columns);
    return matrix;
}

double euclidean_distance(double *matrix, unsigned int i, unsigned int j, unsigned int columns)
{
    double result = 0.0;
    for (int w = 0; w < columns; w++)
    {
        result += ((matrix[(i * columns) + w] - matrix[(j * columns) + w]) * (matrix[(i * columns) + w] - matrix[(j * columns) + w]));
    }

    return (double)sqrt(result);
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

void update_biased_sigma_current(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns)
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

void online_eccentricity_s(
    unsigned int matrix_index,
    double *sample_current,
    double *mi_current,
    double *sigma_current,
    double *eccentricity,
    unsigned int columns)
{
    recursive_mean(mi_current, sample_current, matrix_index, columns);
    update_biased_sigma_current(sigma_current, mi_current, sample_current, matrix_index, columns);
    double dot_product = vec_dot_product(sample_current, mi_current, columns);
    double denominator = (double)(matrix_index + 1.0) * (*sigma_current);

    printf("sample_current ::: %lf\n", *sample_current);
    printf("mi_current ::: %lf\n", *mi_current);
    printf("sigma_current ::: %lf\n", *sigma_current);
    printf("dot_product ::: %lf\n", dot_product);
    printf("denominator ::: %lf\n", denominator);
    printf("(dot_product / denominator) ::: %lf\n", (dot_product / denominator));
    printf("(1.0 / (matrix_index + 1.0)) ::: %lf\n", (1.0 / (matrix_index + 1.0)));
    printf("\n");
    *eccentricity = (1.0 / (matrix_index + 1.0)) + (dot_product / denominator);
    return;
}

TEST_CASE("One dimensional online eccentricity proximity")
{
    unsigned int rows = 4;
    unsigned int columns = 1;
    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double test_1d[4][1] = {{20.0}, {12.0}, {10.0}, {17.0}};
    double *mi_current = (double *)malloc(columns * sizeof(double));
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;

    for (unsigned int i = 0; i < rows; i++)
    {
        online_eccentricity_s(i, test_1d[i], mi_current, sigma_current, eccentricity, columns);
        printf("The eccentricity value is: %lf \n", *eccentricity);
        printf("\n");
    }
    free(mi_current);
    REQUIRE(
        0 == 0);
}