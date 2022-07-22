#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../sqlite/sqlite3.h"

void retrieve_feature_from_table(double *matrix, int rows, int cols, sqlite3 *db)
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
        for (int j = 0; j < cols; j++)
        {
            matrix[(i * cols) + j] = sqlite3_column_double(stmt, j + 1);
        }
        i++;
    }

    sqlite3_finalize(stmt);
    return;
}