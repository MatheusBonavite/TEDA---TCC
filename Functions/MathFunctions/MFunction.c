#include <math.h>

double m_function(unsigned int k)
{
    unsigned int numerator = 3;
    double denominator = exp(-0.007 * (k - 100.0));
    denominator += 1.0;

    return (double)numerator / denominator;
}