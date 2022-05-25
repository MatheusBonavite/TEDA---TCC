void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_biased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns);
void recursive_eccentricity(
    unsigned int matrix_index,
    double *sample_current,
    double *mi_current,
    double *sigma_current,
    double *eccentricity,
    unsigned int columns)
{
    recursive_mean(mi_current, sample_current, matrix_index, columns);
    recursive_biased_sigma(sigma_current, mi_current, sample_current, matrix_index, columns);
    double dot_product = vec_dot_product(sample_current, mi_current, columns);
    double denominator = (double)(matrix_index + 1.0) * (*sigma_current);
    if (denominator > 0.000001)
    {
        *eccentricity = (1.0 / (matrix_index + 1.0)) + (dot_product / denominator);
    }
    return;
}

void recursive_eccentricity_guarded(
    unsigned int matrix_index,
    double *sample_current,
    double *mi_current,
    double *sigma_current,
    double *eccentricity,
    unsigned int columns,
    double variance_limit)
{
    recursive_mean(mi_current, sample_current, matrix_index, columns);
    recursive_biased_sigma(sigma_current, mi_current, sample_current, matrix_index, columns);
    double dot_product = vec_dot_product(sample_current, mi_current, columns);
    double denominator = (double)(matrix_index + 1.0) * (*sigma_current);
    if (*sigma_current > variance_limit && matrix_index <= 3)
    {
        *eccentricity = 1000.0;
        return;
    }
    if (*sigma_current <= 0.000001 && (matrix_index + 1) > 1)
    {
        *eccentricity = (double)(1.0 / (matrix_index + 1.0));
    }
    *eccentricity = (1.0 / (matrix_index + 1.0)) + (dot_product / denominator);
    return;
}