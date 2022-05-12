#include <math.h>
#include <stdio.h>

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

double eccentricity(double *matrix, unsigned int i, unsigned int amount_of_rows, unsigned int amount_of_columns)
{
    double denominator_result = 0.0;
    for (unsigned int j = 0; j < amount_of_rows; j++)
        denominator_result += cumulative_proximity(matrix, j, amount_of_rows, amount_of_columns);
    if (denominator_result > 0.0)
        return ((2.0 * (cumulative_proximity(matrix, i, amount_of_rows, amount_of_columns))) / denominator_result);
    return INFINITY;
}