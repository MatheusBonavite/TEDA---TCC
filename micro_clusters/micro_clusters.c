#include <stdio.h>
#include <stdlib.h>
#include "self_libs/micro_cluster_lib.h"
#include "sqlite/sqlite3.h"

int main(){
    /*To have a registry on the TABLE!*/
    char* err;
    sqlite3* db;
    /*********************************/

    /*Begin - Creating TABLE!*/
    db = either_exists_or_create_table(err, db);
    /*End - Creating TABLE!*/

    /*Begin - Insert into TABLE!*/
    intert_entries_in_table(err, db);
    /*End - Insert into TABLE!*/

    /* Retrieving amount of data rows from the table */
    int rows_x_feature = get_amount_of_data(db);
    printf("\n Amount of data: %i", rows_x_feature);
    /**********************************/

    /* Retrieving amount of data columns from the table */
    unsigned int columns_x_feature = describe_features(db);
    printf("\n Amount of data (columns): %x", columns_x_feature);
    /**********************************/

    /* Memory allocation based on amount of columns and rows */

    //First it will be assumed that all data is of type double, later a more generic way should be implemented.
    //Labels (y) will be assumed to be unsigned integers, and also take one column in table.
    double **x_features;
    x_features = malloc(rows_x_feature * sizeof *x_features);
    for (int i=0; i<rows_x_feature; i++){
        x_features[i] = malloc(columns_x_feature * sizeof *x_features[i]);
    }
    zero_initializer(x_features, rows_x_feature, columns_x_feature);
    retrieve_feature_from_table(x_features, rows_x_feature, columns_x_feature, db);

    /*This will be removed soon */
    for (int i=0; i<rows_x_feature; i++){
        for (int j=0; j<columns_x_feature; j++){
           printf("Matrix [%i][%i] : %lf \t", i, j, x_features[i][j]);
        }
        printf("\n");
    }
    /***************************/

    /**********************************/

    /*Preventing DB Leaks*/
    sqlite3_close(db);
    /*********************/

    /*Preventing memory leaks on x_features and label arrays */
    for (int i=0; i<rows_x_feature; i++){
        free(x_features[i]);
    }
    free(x_features);
    /*********************/
    return 0;
}

