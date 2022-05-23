#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../Header/GlobalHeader.h"

int main()
{
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

    double max_x = 0.0;
    double max_y = 0.0;

    for (unsigned int r_i = 0; r_i < rows; r_i++)
    {
        if (x_features[(r_i * columns)] > max_x)
        {
            max_x = x_features[(r_i * columns)];
        }
        if (x_features[(r_i * columns) + 1] > max_y)
        {
            max_y = x_features[(r_i * columns) + 1];
        }
    }

    for (unsigned int r_i = 0; r_i < rows; r_i++)
    {
        x_features[(r_i * columns)] = x_features[(r_i * columns)] / max_x;
        x_features[(r_i * columns) + 1] = x_features[(r_i * columns) + 1] / max_y;
    }

    for (unsigned int i = 0; i < rows; i++)
    {
        double *test_2d = (double *)calloc(1, columns * sizeof(double));
        for (unsigned int j = 0; j < columns; j++)
        {
            test_2d[j] = x_features[(i * columns) + j];
        }
        micro_clusters_arr = update_micro_cluster(micro_clusters_arr, number_of_micro_clusters, test_2d, i, columns);
        if (i > 1300)
        {
            unsigned int *adj_nodes = (unsigned int *)calloc((n_micro * n_micro), sizeof(unsigned int));
            adjency_matrix(micro_clusters_arr, adj_nodes, n_micro, columns);
            macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_nodes, number_of_macro_clusters, *number_of_micro_clusters);
            regroup_adjency_matrix(macro_clusters_arr, micro_clusters_arr, adj_nodes, *number_of_macro_clusters, *number_of_micro_clusters);
            if (*number_of_macro_clusters > 0)
            {
                for (unsigned int j = 0; j < *number_of_macro_clusters; j++)
                {
                    free(macro_clusters_arr[j].group_of_micro_clusters);
                }
                free(macro_clusters_arr);
                *number_of_macro_clusters = 0;
            }
            macro_clusters_arr = bfs_grouping(macro_clusters_arr, micro_clusters_arr, adj_nodes, number_of_macro_clusters, *number_of_micro_clusters);

            unsigned int which_macro = 0;
            double weird_t_comparison = 0;
            for (unsigned int macro_i = 0; macro_i < *number_of_macro_clusters; macro_i++)
            {
                double density_sum = 0.0;
                double weird_t = 0.0;
                for (unsigned int micro_i = 0; micro_i < macro_clusters_arr[macro_i].n_micro_clusters; micro_i++)
                {
                    unsigned int extract_micro_index = macro_clusters_arr[macro_i].group_of_micro_clusters[micro_i];
                    density_sum += 2.0 / micro_clusters_arr[extract_micro_index].eccentricity;
                }

                for (unsigned int micro_i = 0; micro_i < macro_clusters_arr[macro_i].n_micro_clusters; micro_i++)
                {
                    unsigned int extract_micro_index = macro_clusters_arr[macro_i].group_of_micro_clusters[micro_i];
                    double w_k = (2.0 / micro_clusters_arr[extract_micro_index].eccentricity) / density_sum;
                    double t_k = ((1.0 - micro_clusters_arr[extract_micro_index].eccentricity) / (micro_clusters_arr[extract_micro_index].number_of_data_samples - 2.0));
                    weird_t += w_k + t_k;
                }

                if (weird_t > weird_t_comparison)
                {
                    weird_t_comparison = weird_t;
                    which_macro = macro_i;
                }
            }

            FILE *file;
            file = fopen("./plots/damian_lillard.txt", "a");
            char *buffer = (char *)malloc(sizeof(char) * 250);
            if (buffer == NULL)
            {
                printf("Could not allocate memory \n");
                exit(1);
            }
            sprintf(buffer, "[%u]:", which_macro);
            sprintf(buffer, "%s (%lf) (%lf)\n", buffer, test_2d[0] * max_x, test_2d[1] * max_y);
            unsigned int file_i = 0;
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

            if (i == 1301)
            {
                FILE *file2;
                file = fopen("./plots/damian_lilliard_macro.txt", "w+");
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
            }

            if (*number_of_macro_clusters > 0)
            {
                for (unsigned int j = 0; j < *number_of_macro_clusters; j++)
                {
                    free(macro_clusters_arr[j].group_of_micro_clusters);
                }
                free(macro_clusters_arr);
                *number_of_macro_clusters = 0;
            }
            free(adj_nodes);
        }
        free(test_2d);
    }

    /*Preventing DB Leaks*/
    sqlite3_close(db);
    /*********************/

    /***/
    for (unsigned int j = 0; j < *number_of_micro_clusters; j++)
    {
        free(micro_clusters_arr[j].center);
    }
    free(micro_clusters_arr);
    free(x_features);
    /*********************/
    return 0;
}