void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
double vec_dot_product(double *vector_a, double *vector_b, unsigned int columns);
void recursive_biased_sigma(double *sigma_current, double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns);
void recursive_eccentricity(unsigned int matrix_index, double *sample_current, double *mi_current, double *sigma_current, double *eccentricity, unsigned int columns);