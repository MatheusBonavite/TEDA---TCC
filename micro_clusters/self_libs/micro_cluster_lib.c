#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "micro_cluster_lib.h"
#include "../sqlite/sqlite3.h"


sqlite3* either_exists_or_create_table(char* err, sqlite3* db){

    sqlite3_open("myDBTest.sqlite", &db);
    int response_sql_exec = sqlite3_exec(
        db,
        "CREATE TABLE " 
        "IF NOT EXISTS chameleon_ds4_clean("
        "entry_id INTEGER, x0 REAL, x1 REAL, y INTEGER,"
        "CONSTRAINT entry_pk PRIMARY KEY(entry_id)"
        ");",
        NULL,
        NULL,
        &err
    );

    if(response_sql_exec != SQLITE_OK){
        printf("ERROR! Creating table did not occur as expected! ERROR Log: ");
        printf("\n");
        printf("%s", err);
        printf("\n");
    } else {
        printf("OK! Table creation completed, or table already exists!");
        printf("\n");
    }

    return db;
}

void intert_entries_in_table(char* err, sqlite3* db){
    //Code for reading lines: https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("./automation_tasks/readme.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int response_sql_exec;
    while ((read = getline(&line, &len, fp)) != -1) {
        response_sql_exec = sqlite3_exec(db, line, NULL, NULL, &err);
        if(response_sql_exec!= SQLITE_OK)
            printf("Error during table insert \n Error Log: %s \n", err);
    }

    fclose(fp);
    if (line)
        free(line);
    printf("End of writing on table!");
    return;
}

int get_amount_of_data(sqlite3* db){
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(
        db,
        "SELECT COUNT(*) FROM chameleon_ds4_clean;",
        -1,
        &stmt,
        NULL
    );
    sqlite3_step(stmt);

    int amount_of_entries = sqlite3_column_int(stmt,0);
    sqlite3_finalize(stmt);

    return amount_of_entries;
}

unsigned int describe_features(sqlite3* db){
    unsigned int counter = 0;
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(
        db,
        "PRAGMA TABLE_INFO('chameleon_ds4_clean');",
        -1,
        &stmt,
        NULL
    );
    while(sqlite3_step(stmt) != SQLITE_DONE){
        counter++;
    }
    sqlite3_finalize(stmt);
    return counter-2; //removing two! We do that because one is the id, the other is y... The id will be useless for computation!
}

void zero_matrix_initializer(double** matrix, int rows, int cols){
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            matrix[i][j] = 0;
        }
    }

    /*This will be removed soon */
    for (int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
           printf("Matrix [%i][%i] : %lf \t", i, j, matrix[i][j]);
        }
        printf("\n");
    }
    /***************************/

    return;
}

void zero_array_initializer(int* array, int rows){
    for (int i=0; i<rows; i++){
        array[i] = 0;
    }

    /*This will be removed soon */
    for (int i=0; i<rows; i++){
        printf("Array [%i] : %i \t", i, array[i]);
        printf("\n");
    }
    /***************************/

    return;
}

void retrieve_feature_from_table(double** matrix, int rows, int cols, sqlite3* db){
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(
        db,
        "SELECT * FROM chameleon_ds4_clean;",
        -1,
        &stmt,
        NULL
    );
    
    int i = 0;
    while(sqlite3_step(stmt) != SQLITE_DONE){
        for (int j=0; j<cols; j++){
            matrix[i][j] = sqlite3_column_double(stmt,j+1);
        }
        i++;
    }

    sqlite3_finalize(stmt);
    return;
}

void retrieve_label_from_table(int* array, int amount_of_features, sqlite3* db){
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(
        db,
        "SELECT * FROM chameleon_ds4_clean;",
        -1,
        &stmt,
        NULL
    );
    
    int i =0;
    while(sqlite3_step(stmt) != SQLITE_DONE){
        array[i]= sqlite3_column_double(stmt,amount_of_features+1);
        i++;
    }

    sqlite3_finalize(stmt);
    return;
}

double euclidean_distance(double** matrix, unsigned int k, unsigned int i){
    double cached_first_op = (matrix[k][0] - matrix[i][0]);
    double cached_second_op = (matrix[k][1] - matrix[i][1]);
    double result = 0.0;
    result = cached_first_op * cached_first_op;
    result += cached_second_op * cached_second_op;
    return (double) sqrt(result);
}

double cumulative_proximity(double** matrix, unsigned int k){
    double result = 0.0;
    if(k > 0){
        for(int i=0; i<k; i++){
            result += euclidean_distance(matrix, k, i);
        }
    }
    return result;
}

double offline_eccentricity(double** matrix, unsigned int k){
    if(k < 2){
        printf("\nK must be at least 2! Returning 0.0, may not be the correct result!\n");
        return 0.0;
    }
    double denominator_result = 0.0;
    for(int i=0; i<k; i++)
        denominator_result += cumulative_proximity(matrix, i);

    if(denominator_result > 0)
        return ((2.0*(cumulative_proximity(matrix, k)))/denominator_result);

    printf("\nSum of all cumulative proximities was 0! We can't devide by zero, so returning INF!\n");
    return INFINITY;
}