#include <math.h>

double euclidean_distance(double **matrix, unsigned int k, unsigned int i, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int w = 0; w < amount_of_columns; w++)
    {
        result += ((matrix[k][w] - matrix[i][w]) * (matrix[k][w] - matrix[i][w]));
    }

    return (double)sqrt(result);
}