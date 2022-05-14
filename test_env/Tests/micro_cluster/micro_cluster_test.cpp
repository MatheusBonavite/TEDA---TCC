#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./micro_cluster_test_header.h"

#define ONE_DIMENSION_ROWS 14
#define ONE_DIMENSION_COLS 1

#define TWO_DIMENSION_ROWS 9
#define TWO_DIMENSION_COLS 2

#define THREE_DIMENSION_ROWS 4
#define THREE_DIMENSION_COLS 3

#define FOUR_DIMENSION_ROWS 3
#define FOUR_DIMENSION_COLS 4

double test_1d[ONE_DIMENSION_ROWS * ONE_DIMENSION_COLS] = {
    20.2,
    3.0,
    6.4,
    11.6,
    8.2,
    2.2,
    11.2,
    5.2,
    6.2,
    0.2,
    1.0,
    4.8,
    2.4,
    3.8};
double test_2d[TWO_DIMENSION_ROWS][TWO_DIMENSION_COLS] = {
    {20.2, 3.0},
    {20.19, 3.01},
    {20.18, 3.03},
    {15.0, 3.0},
    {15.01, 3.0},
    {20.18, 3.025},
    {20.18, 3.04},
    {16.0, 3.5},
    {16.5, 3.45}};

double test_3d[THREE_DIMENSION_ROWS * THREE_DIMENSION_COLS] = {
    20.2, 3.0, 6.4,
    11.6, 8.2, 2.2,
    11.2, 5.2, 6.2,
    0.2, 1.0, 4.8};

double test_4d[FOUR_DIMENSION_ROWS * FOUR_DIMENSION_COLS] = {
    20.2, 3.0, 6.4, 11.6,
    8.2, 2.2, 11.2, 5.2,
    6.2, 0.2, 1.0, 4.8};
class TestClass
{
public:
    double *to_test;
    bool check_two_numbers(double, double, double);
    void write_micro_on_file(Micro_Cluster *, unsigned int, unsigned int);
};

bool TestClass::check_two_numbers(double first_val, double sec_val, double epsilon = 0.00001)
{
    return fabs(first_val - sec_val) < epsilon;
}

void TestClass::write_micro_on_file(Micro_Cluster *micro_clusters_arr, unsigned int number_of_micro_clusters, unsigned int columns)
{
    FILE *file = fopen("./plots/micro_clusters.txt", "w+");
    if (file == NULL)
    {
        printf("Could not fopen! \n");
        exit(1);
    }
    for (unsigned int i = 0; i < number_of_micro_clusters; i++)
    {
        char *buffer = (char *)malloc(sizeof(char) * 200);
        if (buffer == NULL)
        {
            printf("Could not allocate memory \n");
            exit(1);
        }
        sprintf(buffer, "[%u]:", i);
        for (unsigned int j = 0; j < columns; j++)
        {
            sprintf(buffer, "%s {%lf}", buffer, micro_clusters_arr[i].center[j]);
        }
        sprintf(buffer, "%s (%lf)", buffer, empirical_m(micro_clusters_arr[i].number_of_data_samples) * sqrt(micro_clusters_arr[i].variance));
        sprintf(buffer, "%s |%lf|", buffer, sqrt(micro_clusters_arr[i].variance));
        sprintf(buffer, "%s ^%lf^\n", buffer, micro_clusters_arr[i].eccentricity);
        int file_i = 0;
        while (file_i < strlen(buffer))
        {
            int result = fputc(buffer[file_i], file);
            if (result == EOF)
            {
                printf("Failed to write character! \n");
                exit(1);
            }
            file_i++;
        }
        free(buffer);
    }
}

TEST_CASE("Two dimensional micro cluster test")
{
    unsigned int n = 0;
    unsigned int *number_of_micro_clusters = &n;
    TestClass T;
    struct Micro_Cluster *micro_clusters_arr;
    for (unsigned int i = 0; i < TWO_DIMENSION_ROWS; i++)
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_2d[i], i, TWO_DIMENSION_COLS);
    T.write_micro_on_file(micro_clusters_arr, *number_of_micro_clusters, TWO_DIMENSION_COLS);
    REQUIRE(true == true);
    free(micro_clusters_arr);
}