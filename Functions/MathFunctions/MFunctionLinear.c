double m_function_linear(unsigned int k)
{
    unsigned int numerator = 3;
    double x = 0.007 * (100.0 - k);
    double denominator = 1 + x;
    denominator += 1.0;

    return (double)numerator / denominator;
}