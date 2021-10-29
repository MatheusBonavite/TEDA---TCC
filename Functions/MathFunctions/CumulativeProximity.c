#include "../../Header/GlobalHeader.h"

double cumulative_proximity(double **matrix, unsigned int k, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int i = 0; i < k; i++)
    {
        result += euclidean_distance(matrix, k, i, amount_of_columns);
    }
    return result;
}