#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../../sqlite/sqlite3.h"

void insert_entries_in_table(char *err, sqlite3 *db)
{
    //Code for reading lines: https://stackoverflow.com/questions/3501338/c-read-file-line-by-line

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("./InfoSource/readme.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int response_sql_exec;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        response_sql_exec = sqlite3_exec(db, line, NULL, NULL, &err);
        if (response_sql_exec != SQLITE_OK)
            printf("Error during table insert \n Error Log: %s \n", err);
    }

    fclose(fp);
    if (line)
        free(line);
    printf("End of writing on table!");
    return;
}