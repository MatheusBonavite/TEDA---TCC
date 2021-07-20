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
    
    /*Preventing DB Leaks*/
    sqlite3_close(db);
    /*********************/
    return 0;
}

