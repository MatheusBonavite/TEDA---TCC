double m_function_second_degree(unsigned int k)
{
    unsigned int numerator = 3;
    double x = 0.007 * (100.0 - k);
    double denominator = 1 + x + (x * x);
    denominator += 1.0;

    return (double)numerator / denominator;
}