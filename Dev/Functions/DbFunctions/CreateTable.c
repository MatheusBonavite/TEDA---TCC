#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../sqlite/sqlite3.h"

sqlite3 *either_exists_or_create_table(char *file_name, char *err, sqlite3 *db)
{

    sqlite3_open(file_name, &db);
    int response_sql_exec = sqlite3_exec(
        db,
        "CREATE TABLE "
        "IF NOT EXISTS chameleon_ds4_clean("
        "entry_id INTEGER, x0 REAL, x1 REAL, y INTEGER,"
        "CONSTRAINT entry_pk PRIMARY KEY(entry_id)"
        ");",
        NULL,
        NULL,
        &err);

    if (response_sql_exec != SQLITE_OK)
    {
        printf("ERROR! Creating table did not occur as expected! ERROR Log: ");
        printf("\n");
        printf("%s", err);
        printf("\n");
    }
    // else
    //{
    //     printf("OK! Table creation completed, or table already exists!");
    //     printf("\n");
    // }

    return db;
}