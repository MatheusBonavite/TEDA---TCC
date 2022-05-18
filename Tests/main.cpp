#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./header/global_header.h"

void write_macro_report(char *file_name, struct Macro_Clusters *macro_clusters_arr, struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_macro_clusters, unsigned int columns)
{
    FILE *file_macros = fopen(file_name, "w+");
    if (file_macros == NULL)
    {
        printf("Could not fopen! \n");
        return;
    }
    for (unsigned int i = 0; i < *number_of_macro_clusters; i++)
    {
        for (unsigned int w = 0; w < macro_clusters_arr[i].n_micro_clusters; w++)
        {
            char *buffer = (char *)calloc(550, sizeof(char));
            if (buffer == NULL)
            {
                printf("Could not allocate memory \n");
                exit(1);
            }
            sprintf(buffer, "[%u]|%u|: Micro Center: ", i, macro_clusters_arr[i].n_micro_clusters);
            unsigned int micro_index = macro_clusters_arr[i].group_of_micro_clusters[w];
            for (unsigned int j = 0; j < columns; j++)
            {
                sprintf(buffer, "%s {%lf}", buffer, micro_clusters_arr[micro_index].center[j]);
            }
            sprintf(buffer, "%s Micro Radius: (%lf)", buffer, empirical_m(micro_clusters_arr[micro_index].number_of_data_samples) * sqrt(micro_clusters_arr[micro_index].variance));
            sprintf(buffer, "%s Micro Variance: %lf", buffer, sqrt(micro_clusters_arr[micro_index].variance));
            sprintf(buffer, "%s Micro Eccentricity: %lf", buffer, micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s Micro Density: %lf", buffer, 2.0 / micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s Micro Density Mean: %lf", buffer, macro_clusters_arr[i].micro_density_mean);
            sprintf(buffer, "%s Micro Index: %u\n", buffer, micro_index);
            int file_i = 0;
            while (file_i < strlen(buffer))
            {
                int result = fputc(buffer[file_i], file_macros);
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
    fclose(file_macros);
    return;
}

void write_samples(char *file_name, double *test_2d)
{
    FILE *file_samples = fopen(file_name, "a+");
    if (file_samples == NULL)
    {
        printf("Could not fopen! \n");
        return;
    }
    int file_i = 0;
    char *buffer = (char *)calloc(50, sizeof(char));
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
    fclose(file_samples);
}

void write_classified_samples(char *file_name, unsigned int class_value, double *test_2d)
{
    FILE *file_samples = fopen(file_name, "a+");
    if (file_samples == NULL)
    {
        printf("Could not fopen! \n");
        return;
    }
    int file_i = 0;
    char *buffer = (char *)calloc(50, sizeof(char));
    sprintf(buffer, "%u %lf %lf \n", class_value, test_2d[0], test_2d[1]);
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
    fclose(file_samples);
}

void write_adjency_matrix_report(char *file_name, unsigned int *adjency_matrix, unsigned n)
{
    FILE *adjency_matrix_file = fopen(file_name, "a+");
    if (adjency_matrix_file == NULL)
    {
        printf("Could not fopen \n");
        return;
    }
    int file_i = 0;
    char *buffer = (char *)calloc((n * n * 50), sizeof(char));

    sprintf(buffer, "Amount of micro_clusters: %u \n", n);
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < n; j++)
        {
            sprintf(buffer, "%s %u", buffer, adjency_matrix[(i * n) + j]);
        }
        sprintf(buffer, "%s \n", buffer);
    }
    sprintf(buffer, "%s \n\n\n", buffer);
    while (file_i < strlen(buffer))
    {
        int result = fputc(buffer[file_i], adjency_matrix_file);
        if (result == EOF)
        {
            printf("Failed to write character! \n");
            exit(1);
        }
        file_i++;
    }
    free(buffer);
    fclose(adjency_matrix_file);
}

void write_micro_report(struct Micro_Cluster *micro_clusters_arr, unsigned number_of_micro_clusters)
{
    FILE *micro_file = fopen("./plots/micro.txt", "a+");
    if (micro_file == NULL)
    {
        printf("Could not fopen \n");
        return;
    }
    int file_i = 0;
    char *buffer = (char *)calloc((number_of_micro_clusters * 350), sizeof(char));

    sprintf(buffer, "Amount of micro_clusters: %u \n", number_of_micro_clusters);
    for (unsigned int i = 0; i < number_of_micro_clusters; i++)
    {
        sprintf(buffer, "%s [%u] Variance: %lf ", buffer, i, micro_clusters_arr[i].variance);
        sprintf(buffer, "%s Eccentricity: %lf ", buffer, micro_clusters_arr[i].eccentricity);
        sprintf(buffer, "%s Center: (%lf , %lf) ", buffer, micro_clusters_arr[i].center[0], micro_clusters_arr[i].center[1]);
        sprintf(buffer, "%s Threshold: %lf ", buffer, micro_clusters_arr[i].outlier_threshold_parameter);
        sprintf(buffer, "%s N_Samples: %u ", buffer, micro_clusters_arr[i].number_of_data_samples);
        sprintf(buffer, "%s \n", buffer);
    }
    sprintf(buffer, "%s \n\n\n", buffer);

    while (file_i < strlen(buffer))
    {
        int result = fputc(buffer[file_i], micro_file);
        if (result == EOF)
        {
            printf("Failed to write character! \n");
            exit(1);
        }
        file_i++;
    }
    free(buffer);
    fclose(micro_file);
}

TEST_CASE("General test for gaussian distribution, centers: [1.0, 2.0], [2.0, 2.0]")
{
    std::default_random_engine e(0.5);
    std::normal_distribution<double> distN(0, 0.25);

    struct Macro_Clusters *macro_clusters_arr;
    unsigned int macr = 0;
    unsigned int *number_of_macro_clusters = &macr;

    unsigned int rows = 4000;
    unsigned int columns = 2;

    struct Micro_Cluster *micro_clusters_arr;
    unsigned int n = 0;
    unsigned int *number_of_micro_clusters = &n;

    double centers[2][2] = {{1.0, 2.0}, {2.0, 2.0}};
    unsigned int center_index = 0;

    unsigned int how_much_exclude = 0;
    unsigned int *how_much_to_exclude = &how_much_exclude;
    unsigned int *inactivate_micros;

    char *samples_file_name = "./plots/samples.txt";
    char *classified_samples_file_name = "./plots/classified_samples.txt";
    char *file_macro_before = "./plots/file_macro_before.txt";
    char *file_macro_after = "./plots/file_macro_after.txt";

    for (unsigned int i = 0; i < rows; i++)
    {
        double *test_2d = (double *)calloc(1, columns * sizeof(double));
        if (test_2d == NULL)
        {
            printf("Could not allocate memory \n");
            exit(1);
        }
        if (i >= 2000)
        {
            center_index = 1;
        }
        test_2d[0] = centers[center_index][0] + distN(e);
        test_2d[1] = centers[center_index][1] + distN(e);
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_2d, i, columns);
        write_samples(samples_file_name, test_2d);

        unsigned int *adj_node = (unsigned int *)calloc(((*number_of_micro_clusters) * (*number_of_micro_clusters)), sizeof(unsigned int));
        if (adj_node == NULL)
        {
            printf("Could not allocate memory \n");
            exit(1);
        }
        adjency_matrix(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns);
        macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, inactivate_micros, number_of_macro_clusters, *number_of_micro_clusters, *how_much_to_exclude);
        if (i == rows - 1)
            write_macro_report(file_macro_before, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, columns);

        if (*how_much_to_exclude > 0)
            free(inactivate_micros);
        else
            *how_much_to_exclude = 0;

        inactivate_micros = regroup_adjency_matrix(macro_clusters_arr, micro_clusters_arr, adj_node, *number_of_macro_clusters, *number_of_micro_clusters, how_much_to_exclude);

        if (*number_of_macro_clusters > 0)
        {
            for (unsigned int j = 0; j < *number_of_macro_clusters; j++)
            {
                free(macro_clusters_arr[j].group_of_micro_clusters);
            }
            free(macro_clusters_arr);
            macro_clusters_arr = NULL;
            *number_of_macro_clusters = 0;
        }
        macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, inactivate_micros, number_of_macro_clusters, *number_of_micro_clusters, *how_much_to_exclude);

        unsigned int which_macro = 0;
        for (unsigned int macro_row = 0; macro_row < *number_of_macro_clusters; macro_row++)
        {
            double weird_t = 0;
            double comparison_weird_t = 0;
            double t_value = 0;
            for (unsigned int micro_row = 0; micro_row < macro_clusters_arr[macro_row].n_micro_clusters; micro_row++)
            {
                unsigned int micro_index_value = macro_clusters_arr[macro_row].group_of_micro_clusters[micro_row];
                double density_sum = macro_clusters_arr[macro_row].micro_density_mean * macro_clusters_arr[macro_row].n_micro_clusters;
                double small_w = (2.0 / micro_clusters_arr[micro_index_value].eccentricity) / density_sum;
                t_value = (1 - micro_clusters_arr[micro_index_value].eccentricity);
                weird_t += small_w + t_value;
            }
            if (comparison_weird_t < weird_t)
            {
                comparison_weird_t = weird_t;
                which_macro = macro_row;
            }
        }
        write_classified_samples(classified_samples_file_name, which_macro, test_2d);
        if (i == rows - 1)
            write_macro_report(file_macro_after, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, columns);

        if (*number_of_macro_clusters > 0)
        {
            for (unsigned int j = 0; j < *number_of_macro_clusters; j++)
            {
                free(macro_clusters_arr[j].group_of_micro_clusters);
            }
            free(macro_clusters_arr);
            macro_clusters_arr = NULL;
            *number_of_macro_clusters = 0;
        }
        free(adj_node);
        free(test_2d);
    }
    if (*number_of_micro_clusters > 0)
    {
        for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
        {
            free(micro_clusters_arr[j].center);
        }
        free(micro_clusters_arr);
    }
    if (*how_much_to_exclude > 0)
        free(inactivate_micros);
    REQUIRE(0 == 0);
}