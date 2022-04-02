#include "../../Header/GlobalHeader.h"

double cumulative_proximity(double **matrix, unsigned int i, unsigned int amount_of_rows, unsigned int amount_of_columns)
{
    double result = 0.0;
    for (int j = 0; j < amount_of_rows; j++)
    {
        result += euclidean_distance(matrix, i, j, amount_of_columns);
    }
    return result;
}