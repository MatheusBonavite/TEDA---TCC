#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../Header/GlobalHeader.h"
#define VARIANCE_LIMIT 0.0007
#define DECAY_VALUE 4000

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
    unsigned int columns)
{
    if (index > after_sample)
    {
        unsigned int which_macro = 0;
        double weird_t_comparison = 0.0;
        unsigned int active_macro_index = 0;

        for (unsigned int index_macro = 0; index_macro < *number_of_macro_clusters; index_macro++)
        {
            if (macro_clusters_arr[index_macro].active == 0)
                continue;
            double weird_t = 0.0;
            for (unsigned int index_micro = 0; index_micro < macro_clusters_arr[active_macro_index].n_micro_clusters; index_micro++)
            {
                if (micro_clusters_arr[index_micro].active == 0)
                    continue;
                double w_t = 1.0;
                double typicality = 0.0;
                double *new_eccentricity = (double *)calloc(1, sizeof(double));
                double *new_variance = (double *)calloc(1, sizeof(double));
                *new_variance = micro_clusters_arr[index_micro].variance;
                double *new_center = (double *)calloc(columns, sizeof(double));
                for (unsigned int w = 0; w < columns; w++)
                    new_center[w] = micro_clusters_arr[index_micro].center[w];
                recursive_eccentricity_guarded(
                    micro_clusters_arr[index_micro].number_of_data_samples + 1,
                    sample,
                    new_center,
                    new_variance,
                    new_eccentricity,
                    columns,
                    VARIANCE_LIMIT);
                double total_density = (macro_clusters_arr[active_macro_index].micro_density_mean * macro_clusters_arr[active_macro_index].n_micro_clusters);
                typicality = (1.0 - (*new_eccentricity / 2.0));
                if (total_density > 0.00001 && micro_clusters_arr[index_micro].eccentricity > 0.00001)
                    w_t = ((2.0 / micro_clusters_arr[index_micro].eccentricity) / total_density);
                weird_t += w_t * typicality;
                free(new_eccentricity);
                free(new_variance);
                free(new_center);
            }
            printf("[%u][>%u<] weird_t ::: %lf density_mean ::: %lf n_micro ::: %u \n", index_macro, active_macro_index, weird_t, macro_clusters_arr[active_macro_index].micro_density_mean, macro_clusters_arr[active_macro_index].n_micro_clusters);
            if (weird_t_comparison < weird_t)
            {
                which_macro = active_macro_index;
                weird_t_comparison = weird_t;
            }
            active_macro_index++;
        }
        write_classified_samples(classified_samples_file_name, which_macro, sample);
    }
    return;
}

int main()
{
    /*Definition of some file names*/
    char *samples_file_name = "./plots/samples.txt";
    char *classified_samples_file_name = "./plots/classified_samples.txt";
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
    db = either_exists_or_create_table(err, db);
    /*End - Creating TABLE!*/

    /*Begin - Insert entries into TABLE!*/
    insert_entries_in_table(err, db);
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

    for (unsigned int i = 0; i < rows; i++)
    {
        printf("Counter %u\n", i);
        double *t_2_d = (double *)calloc(columns, sizeof(double));
        t_2_d[0] = x_features[(i * columns)];
        t_2_d[1] = x_features[(i * columns) + 1];

        micro_clusters_arr = update_micro_cluster_guarded(micro_clusters_arr, number_of_micro_clusters, t_2_d, i, columns, VARIANCE_LIMIT, DECAY_VALUE);
        write_samples(samples_file_name, t_2_d);

        if (i == rows - 1)
        {
            /*Creating Macros After*/
            unsigned int *adj_node = (unsigned int *)calloc(((*number_of_micro_clusters) * (*number_of_micro_clusters)), sizeof(unsigned int));
            if (adj_node == NULL)
            {
                printf("Could not allocate memory \n");
                exit(1);
            }
            adjency_matrix(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns);
            macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, number_of_macro_clusters, *number_of_micro_clusters, 0);
            regroup_adjency_matrix(macro_clusters_arr, micro_clusters_arr, adj_node, *number_of_macro_clusters, *number_of_micro_clusters);
            write_macro_report(file_macro_before, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, columns);
            dealloc_macros(macro_clusters_arr, number_of_macro_clusters);
            free(adj_node);

            adj_node = (unsigned int *)calloc(((*number_of_micro_clusters) * (*number_of_micro_clusters)), sizeof(unsigned int));
            if (adj_node == NULL)
            {
                printf("Could not allocate memory \n");
                exit(1);
            }
            adjency_matrix(micro_clusters_arr, adj_node, *number_of_micro_clusters, columns);
            macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_node, number_of_macro_clusters, *number_of_micro_clusters, 1);
            // filter_macros(macro_clusters_arr, *number_of_macro_clusters);
            write_macro_report(file_macro_after, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, columns);

            free(adj_node);
            /*********************/
        }
        // classify(classified_samples_file_name, t_2_d, macro_clusters_arr, micro_clusters_arr, number_of_macro_clusters, i, rows-1, columns);
        free(t_2_d);
    }
    unsigned int active_micros = 0;
    for (unsigned int i = 0; i < *number_of_micro_clusters; i++)
    {
        if (micro_clusters_arr[i].active == 1)
            active_micros++;
    }
    printf("Amount of active micros are ::: %u || Amount of micros general ::: %u \n", active_micros, *number_of_micro_clusters);
    printf("Amount of macros are ::: %u \n", *number_of_macro_clusters);
    /*Preventing DB Leaks and Micro Leaks | Macro Leaks */
    dealloc_macros(macro_clusters_arr, number_of_macro_clusters);
    dealloc_micros(micro_clusters_arr, number_of_micro_clusters);
    sqlite3_close(db);
    /*********************/

    /***/
    free(x_features);
    /*********************/
    return 0;
}