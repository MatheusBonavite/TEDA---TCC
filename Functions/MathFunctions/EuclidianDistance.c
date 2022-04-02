#include <math.h>

double euclidean_distance(double **matrix, unsigned int i, unsigned int j, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int w = 0; w < amount_of_columns; w++)
    {
        result += ((matrix[i][w] - matrix[j][w]) * (matrix[i][w] - matrix[j][w]));
    }

    return (double)result;
}