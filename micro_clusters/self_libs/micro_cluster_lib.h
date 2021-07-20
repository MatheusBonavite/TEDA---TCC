#include "../sqlite/sqlite3.h"

struct micro_cluster{
    unsigned int number_of_data_samples;
    float center;
    float variance;
    float eccentricity;
    float normalized_eccentricity;
    float typicality;
    float normalized_typicality;
    float density;
    float mki_ski_outlier; 
}; 

float eccentricity(int k, float variance);
unsigned int describe_features(sqlite3* db);
sqlite3* either_exists_or_create_table(char* err, sqlite3* db);
void intert_entries_in_table(char* err, sqlite3* db);
void zero_initializer(double** matrix, int rows, int cols);
int get_amount_of_data(sqlite3* db);