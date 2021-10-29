#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../sqlite/sqlite3.h"

int get_amount_of_data(sqlite3 *db)
{
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(
        db,
        "SELECT COUNT(*) FROM chameleon_ds4_clean;",
        -1,
        &stmt,
        NULL);
    sqlite3_step(stmt);

    int amount_of_entries = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);

    return amount_of_entries;
}