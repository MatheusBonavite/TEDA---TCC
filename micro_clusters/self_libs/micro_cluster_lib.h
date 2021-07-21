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

unsigned int describe_features(sqlite3* db);
sqlite3* either_exists_or_create_table(char* err, sqlite3* db);
void intert_entries_in_table(char* err, sqlite3* db);
void zero_matrix_initializer(double** matrix, int rows, int cols);
void zero_array_initializer(int* array, int rows);
void retrieve_feature_from_table(double** matrix, int rows, int cols, sqlite3* db);
void retrieve_label_from_table(int* array, int amount_of_features, sqlite3* db);
double euclidean_distance(double** matrix, unsigned int k, unsigned int i);
double cumulative_proximity(double** matrix, unsigned int k);
double offline_eccentricity(double** matrix, unsigned int k);
int get_amount_of_data(sqlite3* db);