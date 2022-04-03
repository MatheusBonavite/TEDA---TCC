double outlier_condition(
    double m,
    unsigned int k)
{
    if (m > 0)
        return (double)((double)((m * m) + 1.0)) / ((double)(2.0 * k));
    else
        return 0.0;
}