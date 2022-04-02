#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../Header/GlobalHeader.h"

int main()
{
    /*To have a registry on the TABLE!*/
    char *err;
    sqlite3 *db;
    /*********************************/

    /*Begin - Creating TABLE!*/
    db = either_exists_or_create_table(err, db);
    /*End - Creating TABLE!*/

    /*Begin - Insert entries into TABLE!*/
    insert_entries_in_table(err, db);
    /*End - Insert entries into TABLE!*/

    /*Begin - Retrieving amount of data rows from the table */
    int amount_of_rows = get_amount_of_data(db);
    printf("\n Amount of data: %i", amount_of_rows);
    /*End - Retrieving amount of data rows from the table */

    /*Begin - Retrieving amount of data columns from the table (only features) */
    unsigned int columns_x_feature = describe_features(db);
    printf("\n Amount of data (columns): %x ", columns_x_feature);
    /*End - Retrieving amount of data columns from the table (only features) */

    /*Begin - Memory allocation, for features, based on amount of columns and rows */

    //First it will be assumed that all data is of type double, later a more generic way should be implemented.
    //Labels (y) will be assumed to be unsigned integers, and also take one column in table.
    double **x_features;
    x_features = malloc(amount_of_rows * sizeof *x_features);
    for (int i = 0; i < amount_of_rows; i++)
    {
        x_features[i] = malloc(columns_x_feature * sizeof *x_features[i]);
    }
    zero_matrix_initializer(x_features, amount_of_rows, columns_x_feature);
    retrieve_feature_from_table(x_features, amount_of_rows, columns_x_feature, db);

    /*End - Memory allocation, for features, based on amount of columns and rows */

    /*Begin - Memory allocation, for labels, based on amount of columns and rows */
    int *y_labels;
    y_labels = (int *)malloc(amount_of_rows * sizeof(int));
    zero_array_initializer(y_labels, amount_of_rows);
    retrieve_label_from_table(y_labels, columns_x_feature, db);
    /*End - Memory allocation, for labels, based on amount of columns and rows */

    /*Begin - Testing allocations - This will be removed soon */
    for (int i = 0; i < amount_of_rows; i++)
    {
        for (int j = 0; j < columns_x_feature; j++)
        {
            printf("Matrix [%i][%i] : %lf \t", i, j, x_features[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < amount_of_rows; i++)
    {
        printf("Array [%i] : %i \t", i, y_labels[i]);
        printf("\n");
    }
    /*End - Testing allocations - This will be removed soon */

    /*Begin - Testing distance calculations - This will be removed soon */
    printf("\nEuclidean distance between features(i=0, j=1): %lf", euclidean_distance(x_features, 0, 1, columns_x_feature));
    printf("\nCumulative proximity: %lf", cumulative_proximity(x_features, 1, amount_of_rows, columns_x_feature));
    printf("\nOffline eccentricity: %lf", offline_eccentricity(x_features, columns_x_feature, amount_of_rows, 0));
    /*End - Testing distance calculations - This will be removed soon */

    //All cumulative proximities
    printf("\n");
    for (int x_n = 0; x_n < amount_of_rows; x_n++)
    {
        printf("Cumulative prox x[%d]: %lf", x_n, cumulative_proximity(x_features, x_n, amount_of_rows, columns_x_feature));
        printf("\n");
    }
    /*Preventing DB Leaks*/
    sqlite3_close(db);
    /*********************/

    /***************************/
    //Online eccentricity calculation (example for k=200):

    /*Begin - Initializing initial mi and x_inner_mean */
    double *x_inner_mean = (double *)malloc(columns_x_feature * sizeof(double));
    double *mi = (double *)malloc(columns_x_feature * sizeof(double));
    /*End - Initializing initial mi and x_inner_mean */

    double eccentricity = 0.0;
    double sigma = 0.0;
    double *ptr_sigma = &sigma;

    for (int i = 0; i < 3; i++)
    {
        eccentricity = online_eccentricity(x_features, mi, x_inner_mean, ptr_sigma, columns_x_feature, i);
        printf("\n Mi and Sigma update (outside function):\n ");
        for (int i = 0; i < columns_x_feature; i++)
        {
            printf("\n m[%i] = %lf", i, mi[i]);
        }
        printf("\n eccentricity[%i] = %lf", i, eccentricity);
        printf("\n sigma[%i] = %.14lf", i, sigma);
    }

    printf("\nOnline eccentricity (suppose k=3): %lf", eccentricity);

    /***************************/

    /***/
    for (int i = 0; i < amount_of_rows; i++)
    {
        free(x_features[i]);
    }
    free(mi);
    free(x_inner_mean);
    free(x_features);
    free(y_labels);
    /*********************/
    return 0;
}