
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../sqlite/sqlite3.h"

void retrieve_label_from_table(int *array, int amount_of_features, sqlite3 *db)
{
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
        db,
        "SELECT * FROM chameleon_ds4_clean;",
        -1,
        &stmt,
        NULL);

    int i = 0;
    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        array[i] = sqlite3_column_double(stmt, amount_of_features + 1);
        i++;
    }

    sqlite3_finalize(stmt);
    return;
}