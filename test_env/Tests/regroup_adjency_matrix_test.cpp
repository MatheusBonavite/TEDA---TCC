#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./header/global_header.h"

TEST_CASE("Regroup adjency matrix test for 4x(1-x)")
{
    /* Create random engine with the help of seed */
    std::default_random_engine e(0.5);

    /* declaring normal distribution object 'distN' and initializing its mean and standard deviation fields. */
    /* Mean and standard deviation are distribution parameters of Normal distribution. Here, we have used mean=5, and standard deviation=2. You can take mean and standard deviation as per your choice */
    std::normal_distribution<double> distN(0, 0.25);
    FILE *file_samples = fopen("./plots/samples.txt", "w+");
    if (file_samples == NULL)
    {
        printf("Could not fopen! \n");
        exit(1);
    }
    struct Macro_Clusters *macro_clusters_arr;
    unsigned int macr = 0;
    unsigned int *number_of_macro_clusters = &macr;
    unsigned int problem_dimension = 2;
    unsigned int rows = 4000;
    unsigned int columns = 2;
    unsigned int n = 0;
    double *matrix = matrix_allocation(rows, columns);
    struct Micro_Cluster *micro_clusters_arr;
    unsigned int *number_of_micro_clusters = &n;

    double centers[2][2] = {{1.0, 2.0}, {2.0, 2.0}};
    unsigned int center_index = 0;
    for (unsigned int i = 0; i < rows; i++)
    {
        double *test_2d = (double *)calloc(1, columns * sizeof(double));
        if (i >= 2000)
        {
            center_index = 1;
        }

        if (test_2d == NULL)
        {
            printf("Could not allocate memory \n");
            exit(1);
        }
        test_2d[0] = centers[center_index][0] + distN(e);
        test_2d[1] = centers[center_index][1] + distN(e);
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_2d, i, columns);

        int file_i = 0;
        char *buffer = (char *)malloc(sizeof(char) * 50);
        sprintf(buffer, "%lf %lf \n", test_2d[0], test_2d[1]);
        while (file_i < strlen(buffer))
        {
            int result = fputc(buffer[file_i], file_samples);
            if (result == EOF)
            {
                printf("Failed to write character! \n");
                exit(1);
            }
            file_i++;
        }
        free(buffer);
        free(test_2d);
    }
    unsigned int *adj_node = (unsigned int *)calloc(((*number_of_micro_clusters) * (*number_of_micro_clusters)), sizeof(unsigned int));
    adjency_matrix(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns);
    unsigned int hits = 0;
    unsigned int misses = 0;
    for (unsigned int w = 0; w < *number_of_micro_clusters; w++)
    {
        for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
        {
            if (adj_node[(w * (*number_of_micro_clusters)) + j] == 1)
            {
                hits++;
            }
            if (adj_node[(w * (*number_of_micro_clusters)) + j] == 0)
            {
                misses++;
            }
        }
    }
    printf("Amount of hits ::: %u \n", hits);
    printf("Amount of misses ::: %u \n", misses);
    printf("\n\n\n");
    macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, number_of_macro_clusters, *number_of_micro_clusters);
    printf("Amount of macro [BEFORE] ::: %u \n", *number_of_macro_clusters);
    printf("Amount of micro [BEFORE] ::: %u \n", *number_of_micro_clusters);
    printf("\n\n\n");

    FILE *file_before = fopen("./plots/adjency_test_before.txt", "w+");
    if (file_before == NULL)
    {
        printf("Could not fopen! \n");
        exit(1);
    }
    for (unsigned int i = 0; i < *number_of_macro_clusters; i++)
    {
        for (unsigned int w = 0; w < macro_clusters_arr[i].n_micro_clusters; w++)
        {
            char *buffer = (char *)malloc(sizeof(char) * 250);
            if (buffer == NULL)
            {
                printf("Could not allocate memory \n");
                exit(1);
            }
            sprintf(buffer, "[%u]:", i);
            unsigned int micro_index = macro_clusters_arr[i].group_of_micro_clusters[w];
            for (unsigned int j = 0; j < columns; j++)
            {
                sprintf(buffer, "%s {%lf}", buffer, micro_clusters_arr[micro_index].center[j]);
            }
            sprintf(buffer, "%s (%lf)", buffer, empirical_m(micro_clusters_arr[micro_index].number_of_data_samples) * sqrt(micro_clusters_arr[micro_index].variance));
            sprintf(buffer, "%s |%lf|", buffer, sqrt(micro_clusters_arr[micro_index].variance));
            sprintf(buffer, "%s ^%lf^", buffer, micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s /%lf/", buffer, 2.0 / micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s ~%lf~", buffer, macro_clusters_arr[i].micro_density_mean);
            sprintf(buffer, "%s >%u<", buffer, macro_clusters_arr[i].n_micro_clusters);
            sprintf(buffer, "%s ?%u?\n", buffer, micro_index);
            int file_i = 0;
            while (file_i < strlen(buffer))
            {
                int result = fputc(buffer[file_i], file_before);
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

    regroup_adjency_matrix(macro_clusters_arr, micro_clusters_arr, adj_node, *number_of_macro_clusters, *number_of_micro_clusters);
    for (unsigned int j = 0; j < *number_of_macro_clusters; j++)
    {
        free(macro_clusters_arr[j].group_of_micro_clusters);
    }
    free(macro_clusters_arr);
    macro_clusters_arr = NULL;
    *number_of_macro_clusters = 0;

    hits = 0;
    misses = 0;
    for (unsigned int w = 0; w < *number_of_micro_clusters; w++)
    {
        for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
        {
            if (adj_node[(w * (*number_of_micro_clusters)) + j] == 1)
            {
                hits++;
            }
            if (adj_node[(w * (*number_of_micro_clusters)) + j] == 0)
            {
                misses++;
            }
        }
    }

    printf("Amount of hits [AFTER] ::: %u \n", hits);
    printf("Amount of misses [AFTER] ::: %u \n", misses);
    printf("\n\n\n");
    macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, number_of_macro_clusters, *number_of_micro_clusters);
    printf("Amount of macro [AFTER] ::: %u \n", *number_of_macro_clusters);
    printf("Amount of micro [AFTER] ::: %u \n", *number_of_micro_clusters);
    printf("\n\n\n");

    FILE *file = fopen("./plots/adjency_test_after.txt", "w+");
    if (file == NULL)
    {
        printf("Could not fopen! \n");
        exit(1);
    }
    for (unsigned int i = 0; i < *number_of_macro_clusters; i++)
    {
        for (unsigned int w = 0; w < macro_clusters_arr[i].n_micro_clusters; w++)
        {
            char *buffer = (char *)malloc(sizeof(char) * 250);
            if (buffer == NULL)
            {
                printf("Could not allocate memory \n");
                exit(1);
            }
            sprintf(buffer, "[%u]:", i);
            unsigned int micro_index = macro_clusters_arr[i].group_of_micro_clusters[w];
            for (unsigned int j = 0; j < columns; j++)
            {
                sprintf(buffer, "%s {%lf}", buffer, micro_clusters_arr[micro_index].center[j]);
            }
            sprintf(buffer, "%s (%lf)", buffer, empirical_m(micro_clusters_arr[micro_index].number_of_data_samples) * sqrt(micro_clusters_arr[micro_index].variance));
            sprintf(buffer, "%s |%lf|", buffer, sqrt(micro_clusters_arr[micro_index].variance));
            sprintf(buffer, "%s ^%lf^", buffer, micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s /%lf/", buffer, 2.0 / micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s ~%lf~", buffer, macro_clusters_arr[i].micro_density_mean);
            sprintf(buffer, "%s >%u<", buffer, macro_clusters_arr[i].n_micro_clusters);
            sprintf(buffer, "%s ?%u?\n", buffer, micro_index);
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
    for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
    {
        free(micro_clusters_arr[j].center);
    }
    for (unsigned int j = 0; j < *number_of_macro_clusters; j++)
    {
        free(macro_clusters_arr[j].group_of_micro_clusters);
    }
    free(macro_clusters_arr);
    free(adj_node);
    REQUIRE(0 == 0);
}