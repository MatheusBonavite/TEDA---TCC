#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./adjency_matrix_test_header.h"

#define TWO_DIMENSION_ROWS 10
#define TWO_DIMENSION_COLS 2

double test_2d[TWO_DIMENSION_ROWS][TWO_DIMENSION_COLS] = {
    {20.2, 3.0},
    //{20.18, 3.035},
    {20.19, 3.01},
    {20.18, 3.03},
    {20.18, 3.04},
    {15.0, 3.0},
    {15.01, 3.0},
    {20.18, 3.025},
    {16.0, 3.5},
    {20.18, 3.035},
    {16.5, 3.45}};
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

TEST_CASE("Two dimensional micro cluster grouping test")
{
    unsigned int n = 0;
    unsigned int *number_of_micro_clusters = &n;
    TestClass T;
    struct Micro_Cluster *micro_clusters_arr;
    for (unsigned int i = 0; i < TWO_DIMENSION_ROWS; i++)
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_2d[i], i, TWO_DIMENSION_COLS);
    unsigned int *adj_nodes = (unsigned int *)calloc((n * n), sizeof(unsigned int));
    adjency_matrix(micro_clusters_arr, adj_nodes, n, TWO_DIMENSION_COLS);
    unsigned int hits = 0;
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            printf("__adj_node[%u][%u]__: %u\n", i, j, adj_nodes[(i * n) + j]);
            if (adj_nodes[(i * n) + j] == 1)
            {
                hits++;
            }
        }
    }
    REQUIRE(T.check_two_numbers((double)hits, 2.0) == true);
    free(micro_clusters_arr);
    free(adj_nodes);
}