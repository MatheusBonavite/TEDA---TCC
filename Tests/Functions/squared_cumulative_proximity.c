double squared_euclidean_distance(double *matrix, unsigned int i, unsigned int j, unsigned int columns);
double squared_cumulative_proximity(double *matrix, unsigned int i, unsigned int rows, unsigned int columns)
{
    double result = 0.0;
    for (int j = 0; j < rows; j++)
    {
        result += squared_euclidean_distance(matrix, i, j, columns);
    }
    return result;
}