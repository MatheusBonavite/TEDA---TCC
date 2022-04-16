#define CATCH_CONFIG_MAIN
#include "../catch.hh"
#include <stdlib.h>

void recursive_mean(double *mi_current, double *sample_current, unsigned int matrix_index, unsigned int columns)
{
    if (matrix_index == 0)
    {
        for (unsigned int j = 0; j < columns; j++)
        {
            mi_current[j] = sample_current[j];
        }
        return;
    }
    double first_fraction = (double)(matrix_index) / (matrix_index + 1.0);
    double second_fraction = (double)(1.0) / (matrix_index + 1.0);
    for (unsigned int j = 0; j < columns; j++)
    {
        mi_current[j] = (first_fraction * mi_current[j]) + (second_fraction * sample_current[j]);
    }
    return;
}

TEST_CASE("One dimensional recursive mean test")
{
    unsigned int rows = 14;
    unsigned int columns = 1;
    double mean = 0.0;
    double *mi_current = &mean;

    double test_1d[14][1] = {{20.2}, {3.0}, {6.4}, {11.6}, {8.2}, {2.2}, {11.2}, {5.2}, {6.2}, {0.2}, {1.0}, {4.8}, {2.4}, {3.8}};
    double results[14][1] = {{20.200000},
                             {11.600000},
                             {9.866667},
                             {10.300000},
                             {9.880000},
                             {8.600000},
                             {8.971429},
                             {8.500000},
                             {8.244444},
                             {7.440000},
                             {6.854545},
                             {6.683333},
                             {6.353846},
                             {6.171429}};
    for (unsigned int i = 0; i < rows; i++)
    {
        recursive_mean(mi_current, test_1d[i], i, columns);
        REQUIRE(fabs(*mi_current - results[i][0]) < 0.00001);
    }
}
