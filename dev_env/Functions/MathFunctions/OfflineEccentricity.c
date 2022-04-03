#include <math.h>
#include <stdio.h>
#include "../../Header/GlobalHeader.h"

double offline_eccentricity(double **matrix, unsigned int amount_of_columns, unsigned int amount_of_rows, unsigned int i)
{

    if ((amount_of_rows + 1.0) <= 2)
    {
        printf("\nK must be greater than 2! Returning 1.0, may not be the correct result!\n");
        return 1.0;
    }
    double denominator_result = 0.0;
    for (unsigned int j = 0; j < amount_of_rows; j++)
        denominator_result += cumulative_proximity(matrix, j, amount_of_rows, amount_of_columns);
    if (denominator_result > 0.0)
        return ((2.0 * (cumulative_proximity(matrix, i, amount_of_rows, amount_of_columns))) / denominator_result);
    printf("\nSum of all cumulative proximities was 0! We can't devide by zero, so returning INF!\n");
    return INFINITY;
}