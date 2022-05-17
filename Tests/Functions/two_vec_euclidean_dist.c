#include <math.h>

double two_vec_euclidean_distance(double *a, double *b, unsigned int columns)
{
    double result = 0.0;
    for (int w = 0; w < columns; w++)
    {
        result += ((a[w] - b[w]) * (a[w] - b[w]));
    }

    return (double)sqrt(result);
}