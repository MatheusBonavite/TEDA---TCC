double euclidean_distance(double *matrix, unsigned int i, unsigned int j, unsigned int columns)
{
    double result = 0.0;
    for (int w = 0; w < columns; w++)
    {
        result += ((matrix[(i * columns) + w] - matrix[(j * columns) + w]) * (matrix[(i * columns) + w] - matrix[(j * columns) + w]));
    }

    return (double)sqrt(result);
}

double cumulative_proximity(double *matrix, unsigned int i, unsigned int rows, unsigned int columns)
{
    double result = 0.0;
    for (int j = 0; j < rows; j++)
    {
        result += euclidean_distance(matrix, i, j, columns);
    }
    return result;
}