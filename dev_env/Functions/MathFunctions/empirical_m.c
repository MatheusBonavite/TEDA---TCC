#include <math.h>

double empirical_m(int k)
{
    double denominator = exp(-0.007 * (k - 100.0));
    return (3.0 / (1.0 + denominator));
}