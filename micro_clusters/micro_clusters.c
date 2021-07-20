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
    int get_amount_of_values = get_amount_of_data(db);
    printf("\n Amount of data: %i", get_amount_of_values);
    /**********************************/

    /* Retrieving amount of data columns from the table */
    unsigned int get_amount_of_columns = describe_features(db);
    printf("\n Amount of data (columns): %x", get_amount_of_columns);
    /**********************************/

    /* Memory allocation based on amount of columns and rows */

    //First it will be assumed that all data is of type double, later a more generic way should be implemented.
    //Labels (y) will be assumed to be integers.
    double **x_features;
    x_features = malloc(get_amount_of_values * sizeof *x_features);
    for (int i=0; i<get_amount_of_values; i++){
        x_features[i] = malloc(get_amount_of_columns * sizeof *x_features[i]);
    }
    zero_initializer(x_features, get_amount_of_values,get_amount_of_columns);

    /**********************************/
    
    /*Preventing DB Leaks*/
    sqlite3_close(db);
    /*********************/

    /*Preventing memory leaks on x_features and label arrays */
    for (int i=0; i<get_amount_of_values; i++){
        free(x_features[i]);
    }
    free(x_features);
    /*********************/
    return 0;
}

