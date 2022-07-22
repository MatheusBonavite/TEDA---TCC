#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../sqlite/sqlite3.h"

unsigned int describe_features(sqlite3 *db)
{
    unsigned int counter = 0;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
        db,
        "PRAGMA TABLE_INFO('chameleon_ds4_clean');",
        -1,
        &stmt,
        NULL);
    while (sqlite3_step(stmt) != SQLITE_DONE)
    {
        counter++;
    }
    sqlite3_finalize(stmt);
    return counter - 2; //removing two! We do that because one is the id, the other is y... The id will be useless for computation!
}