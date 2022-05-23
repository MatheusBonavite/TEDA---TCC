void zero_matrix_initializer(double *matrix, unsigned int rows, unsigned int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[(columns * i) + j] = 0;
        }
    }
    return;
}