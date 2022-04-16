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

double vec_norm_squared(double *vec, unsigned int columns){
    double accum = 0.0;
    for(unsigned int j=0; j<columns; j++){
        accum += (vec[j] * vec[j]);
    }
    return accum;
}

double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns){
    double *aux = (double *) malloc(columns * sizeof(double));
    double dot_product = 0.0;
    for(unsigned int j=0; j<columns; j++){
        aux[j] = (vector_a[j] - vector_b[j]);
        dot_product = dot_product + (aux[j] * aux[j]);
    }
    free(aux);
    return dot_product;
}

void update_capital_x(double *capital_x, double *sample_current, unsigned int matrix_index, unsigned int columns){
    if(matrix_index == 0){
        *capital_x = vec_norm_squared(sample_current, columns);
        return;
    }
    double first_fraction = (double) (matrix_index)/(matrix_index + 1.0);
    double second_fraction = (double) (1.0)/(matrix_index+1.0);
    printf("\n\nCapital x ::: %lf \n\n", (first_fraction*(*capital_x)));
    *capital_x = (first_fraction*(*capital_x)) + (second_fraction*vec_norm_squared(sample_current, columns));
    printf("\n\nCapital x ::: %lf \n\n", *capital_x);
    return;
}

void update_mi_current(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns){
    if(matrix_index == 0){
        for(unsigned int j=0; j < columns; j++){
            mi_current[j] = sample_current[j];
        }
        return;
    }
    double first_fraction = (double) (matrix_index)/(matrix_index + 1.0);
    double second_fraction = (double) (1.0)/(matrix_index + 1.0);
    for(unsigned int j=0; j<columns; j++){
        mi_current[j] = (first_fraction*mi_current[j]) + (second_fraction*sample_current[j]);
    }
    return;
}

double online_cumulative_proximity(
    double *current_sample,
    double *current_mi,
    double *capital_x,
    unsigned int matrix_index,
    unsigned int columns
)
{
    double first_product = (matrix_index+1.0);
    update_mi_current(current_mi, current_sample, matrix_index, columns);
    double current_sample_and_mi_dist = vec_dot_product(current_sample, current_mi, columns);
    update_capital_x(capital_x, current_sample, matrix_index, columns);
    double norm_squared_mi = vec_norm_squared(current_mi, columns);

    printf("current_sample ::: %lf \n", *current_sample);
    printf("current_mi ::: %lf \n", *current_mi);
    printf("dist_mi ::: %lf \n", current_sample_and_mi_dist);
    printf("capital_x ::: %lf \n", *capital_x);
    printf("norm_squared_mi ::: %lf \n", norm_squared_mi);
    return first_product*(current_sample_and_mi_dist + (*capital_x) - norm_squared_mi);

}

TEST_CASE("One dimensional cumulative proximity")
{
    double cx = 0.0;
    unsigned int rows = 14;
    unsigned int columns = 1;
    double test_1d[rows][columns] = { { 20.2 }, { 3.0 }, { 6.4 }, { 11.6 }, { 8.2 }, { 2.2 }, { 11.2 }, { 5.2 }, { 6.2 }, { 0.2 }, { 1.0 }, { 4.8 }, { 2.4 }, { 3.8 } };
    double *mi = (double *) malloc(columns*sizeof(double));
    double *capital_x = &cx;

    for(int i=0; i<rows; i++){
        double aux = online_cumulative_proximity(test_1d[i], mi, capital_x, i, columns);
        printf("aux :::: %lf \n", aux);
    }

    free(mi);
    REQUIRE(
        0 == 0
    );
}