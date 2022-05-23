#include <math.h>
double cumulative_proximity(double *matrix, unsigned int i, unsigned int rows, unsigned int columns);
double eccentricity(double *matrix, unsigned int i, unsigned int amount_of_rows, unsigned int amount_of_columns)
{
    double denominator_result = 0.0;
    for (unsigned int j = 0; j < amount_of_rows; j++)
        denominator_result += cumulative_proximity(matrix, j, amount_of_rows, amount_of_columns);
    if (denominator_result > 0.0)
        return ((2.0 * (cumulative_proximity(matrix, i, amount_of_rows, amount_of_columns))) / denominator_result);
    return INFINITY;
}