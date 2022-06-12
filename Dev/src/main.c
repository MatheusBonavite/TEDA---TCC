#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../Header/GlobalHeader.h"
#define VARIANCE_LIMIT 0.0015
#define DECAY_VALUE 3000
#define EPS (1e-10)

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
        if (macro_clusters_arr[i].active == 0)
            continue;
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
            if (micro_clusters_arr[micro_index].active == 0)
            {
                free(buffer);
                continue;
            }
            for (unsigned int j = 0; j < columns; j++)
            {
                sprintf(buffer, "%s {%lf}", buffer, micro_clusters_arr[micro_index].center[j]);
            }
            sprintf(buffer, "%s Micro Radius: (%lf)", buffer, empirical_m(micro_clusters_arr[micro_index].number_of_data_samples) * sqrt(micro_clusters_arr[micro_index].variance));
            sprintf(buffer, "%s Micro Variance: %lf", buffer, micro_clusters_arr[micro_index].variance);
            sprintf(buffer, "%s Micro Eccentricity: %lf", buffer, micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s Micro Density: %lf", buffer, 2.0 / micro_clusters_arr[micro_index].eccentricity);
            sprintf(buffer, "%s Micro Samples: %u", buffer, micro_clusters_arr[micro_index].number_of_data_samples);
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

void print_micro_report(struct Micro_Cluster *micro_clusters_arr, unsigned number_of_micro_clusters)
{
    for (unsigned int i = 0; i < number_of_micro_clusters; i++)
    {
        printf("[%u] Variance: %lf \n", i, micro_clusters_arr[i].variance);
        printf("Eccentricity: %lf \n", micro_clusters_arr[i].eccentricity);
        printf("Center: (%lf , %lf) \n", micro_clusters_arr[i].center[0], micro_clusters_arr[i].center[1]);
        printf("N_Samples: %u \n", micro_clusters_arr[i].number_of_data_samples);
        printf("Active: %u \n\n", micro_clusters_arr[i].active);
    }
    printf("\n\n\n");
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
        sprintf(buffer, "%s N_Samples: %u ", buffer, micro_clusters_arr[i].number_of_data_samples);
        sprintf(buffer, "%s Active: %u ", buffer, micro_clusters_arr[i].active);
        sprintf(buffer, "%s Life: %lf ", buffer, micro_clusters_arr[i].life);
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

void filter_macros(struct Macro_Clusters *macro_clusters_arr, unsigned int macros_amount)
{
    double amount_of_micros_mean = 0.0;
    for (unsigned int i = 0; i < macros_amount; i++)
        amount_of_micros_mean += macro_clusters_arr[i].n_micro_clusters;
    amount_of_micros_mean = amount_of_micros_mean / macros_amount;
    for (unsigned int i = 0; i < macros_amount; i++)
    {
        if (macro_clusters_arr[i].n_micro_clusters < (0.25 * amount_of_micros_mean))
            macro_clusters_arr[i].active = 0;
        else
            macro_clusters_arr[i].active = 1;
    }
    return;
}

void dealloc_micros(struct Micro_Cluster *micro_clusters_arr, unsigned int *number_of_micro_clusters)
{
    if (*number_of_micro_clusters > 0)
    {
        for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
        {
            free(micro_clusters_arr[j].center);
        }
        free(micro_clusters_arr);
    }
    return;
}

void dealloc_macros(struct Macro_Clusters *macro_clusters_arr, unsigned int *number_of_macro_clusters)
{
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
    return;
}

void classify(
    char *classified_samples_file_name,
    double *sample,
    struct Macro_Clusters *macro_clusters_arr,
    struct Micro_Cluster *micro_clusters_arr,
    unsigned int *number_of_macro_clusters,
    unsigned int index,
    unsigned int after_sample,
    unsigned int columns,
    double variance_limit)
{

    unsigned int active_macro_index = 0;
    unsigned int which_macro = 0;
    double weird_t_comparison = 0.0;
    for (unsigned int index_macro = 0; index_macro < *number_of_macro_clusters; index_macro++)
    {
        double weird_t = 0.0;
        double total_density = (macro_clusters_arr[active_macro_index].micro_density_mean * macro_clusters_arr[active_macro_index].n_micro_clusters);
        for (unsigned int i = 0; i < macro_clusters_arr[active_macro_index].n_micro_clusters; i++)
        {
            unsigned int index_micro = macro_clusters_arr[active_macro_index].group_of_micro_clusters[i];
            if (micro_clusters_arr[index_micro].number_of_data_samples < 2)
                continue;

            double *new_eccentricity = (double *)calloc(1, sizeof(double));
            double *new_variance = (double *)calloc(1, sizeof(double));
            *new_variance = micro_clusters_arr[index_micro].variance;
            double *new_center = (double *)calloc(columns, sizeof(double));
            for (unsigned int w = 0; w < columns; w++)
                new_center[w] = micro_clusters_arr[index_micro].center[w];
            recursive_eccentricity_guarded(
                micro_clusters_arr[index_micro].number_of_data_samples,
                sample,
                new_center,
                new_variance,
                new_eccentricity,
                columns,
                variance_limit);
            double tipicality = (double)(1.0 - (*new_eccentricity)) / ((double)micro_clusters_arr[index_micro].number_of_data_samples - (double)1.0);
            double w_t = ((2.0 / (*new_eccentricity)) / total_density);
            weird_t += (w_t * tipicality);
            free(new_eccentricity);
            free(new_variance);
            free(new_center);
        }
        // printf("[%u] weird_t ::: %lf | weird_t_comparison ::: %lf \n", active_macro_index, weird_t, weird_t_comparison);
        if (weird_t_comparison < weird_t)
        {
            which_macro = active_macro_index;
            weird_t_comparison = weird_t;
        }
        active_macro_index++;
    }
    write_classified_samples(classified_samples_file_name, which_macro, sample);
    return;
}

int main()
{

    for (unsigned int std_value_d = 0; std_value_d < 20; std_value_d++)
    {
        /*Definition of some file names*/
        char file_to_grab[125];
        snprintf(file_to_grab, 125, "./InfoSource/std_3/std_%d.txt", std_value_d);
        char db_name[125];
        snprintf(db_name, 125, "myDBTest_%d.sqlite", std_value_d);

        // char *file_to_grab = "./InfoSource/std_1.txt";
        char *samples_file_name = "./plots/samples.txt";
        char *file_micro_name = "./plots/micro.txt";
        char *file_macro_before = "./plots/file_macro_before.txt";
        char *file_macro_after = "./plots/file_macro_after.txt";
        /*********************************/
        /*To have a registry on the TABLE!*/
        char *err;
        sqlite3 *db;
        struct Micro_Cluster *micro_clusters_arr;
        struct Macro_Clusters *macro_clusters_arr;
        unsigned int n_micro = 0;
        unsigned int n_macro = 0;
        unsigned int *number_of_micro_clusters = &n_micro;
        unsigned int *number_of_macro_clusters = &n_macro;
        /*********************************/

        /*Begin - Creating TABLE!*/
        db = either_exists_or_create_table(db_name, err, db);
        /*End - Creating TABLE!*/

        /*Begin - Insert entries into TABLE!*/
        insert_entries_in_table(err, file_to_grab, db);
        /*End - Insert entries into TABLE!*/

        /*Begin - Retrieving amount of data rows from the table */
        int rows = get_amount_of_data(db);
        printf("\n Amount of data: %i", rows);
        /*End - Retrieving amount of data rows from the table */

        /*Begin - Retrieving amount of data columns from the table (only features) */
        unsigned int columns = describe_features(db);
        printf("\n Amount of data (columns): %u\n", columns);
        /*End - Retrieving amount of data columns from the table (only features) */

        double *x_features = (double *)calloc(rows * columns, sizeof(double));
        retrieve_feature_from_table(x_features, rows, columns, db);
        unsigned int the_value = 0;
        for (double r_factor = 1.0; r_factor < 5.0; r_factor += 0.25)
        {
            for (double variance_limit = 0.0; variance_limit < 0.0030; variance_limit += 0.0001)
            {
                char classified_samples_file_name[55];
                snprintf(classified_samples_file_name, 55, "./samples_test/std_3_%d/classified_samples%d.txt", std_value_d, the_value);

                for (unsigned int i = 0; i < rows; i++)
                {
                    printf("Counter %u\n", i);
                    double *t_2_d = (double *)calloc(columns, sizeof(double));
                    t_2_d[0] = x_features[(i * columns)];
                    t_2_d[1] = x_features[(i * columns) + 1];

                    micro_clusters_arr = update_micro_cluster_guarded(micro_clusters_arr, number_of_micro_clusters, t_2_d, i, columns, variance_limit, DECAY_VALUE);
                    // write_samples(samples_file_name, t_2_d);

                    if (i == rows - 1)
                    {
                        /*Creating Macros After*/
                        unsigned int *adj_node = (unsigned int *)calloc(((*number_of_micro_clusters) * (*number_of_micro_clusters)), sizeof(unsigned int));
                        if (adj_node == NULL)
                        {
                            printf("Could not allocate memory \n");
                            exit(1);
                        }
                        adjency_matrix_diff(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns, r_factor); // adjency_matrix(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns);
                        macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, number_of_macro_clusters, *number_of_micro_clusters, 1);
                        regroup_adjency_matrix(macro_clusters_arr, micro_clusters_arr, adj_node, *number_of_macro_clusters, *number_of_micro_clusters);
                        // write_macro_report(file_macro_before, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, columns);
                        dealloc_macros(macro_clusters_arr, number_of_macro_clusters);
                        free(adj_node);

                        adj_node = (unsigned int *)calloc(((*number_of_micro_clusters) * (*number_of_micro_clusters)), sizeof(unsigned int));
                        if (adj_node == NULL)
                        {
                            printf("Could not allocate memory \n");
                            exit(1);
                        }
                        adjency_matrix_diff(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns, r_factor); // adjency_matrix(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns);
                        macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, number_of_macro_clusters, *number_of_micro_clusters, 1);
                        // filter_macros(macro_clusters_arr, *number_of_macro_clusters);
                        // write_macro_report(file_macro_after, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, columns);
                        free(adj_node);
                        /*********************/
                    }
                    // if (i == rows - 1)
                    //     write_micro_report(micro_clusters_arr, *number_of_micro_clusters);
                    // classify(classified_samples_file_name, t_2_d, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, i, rows-1, columns);
                    free(t_2_d);
                }
                for (unsigned int i = 0; i < rows; i++)
                {
                    double *t_2_d = (double *)calloc(columns, sizeof(double));
                    t_2_d[0] = x_features[(i * columns)];
                    t_2_d[1] = x_features[(i * columns) + 1];
                    classify(classified_samples_file_name, t_2_d, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, i, rows - 1, columns, variance_limit);
                    free(t_2_d);
                }
                /*Preventing DB Leaks and Micro Leaks | Macro Leaks */
                dealloc_macros(macro_clusters_arr, number_of_macro_clusters);
                dealloc_micros(micro_clusters_arr, number_of_micro_clusters);
                /*********************/
                the_value++;
            }
        }
        /***/
        sqlite3_close(db);
        free(x_features);
        /*********************/
    }
    return 0;
}