#pragma once
#include "../sqlite/sqlite3.h"

struct micro_cluster
{
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

unsigned int describe_features(sqlite3 *db);
sqlite3 *either_exists_or_create_table(char *err, sqlite3 *db);
void insert_entries_in_table(char *err, sqlite3 *db);
void zero_matrix_initializer(double **matrix, int rows, int cols);
void zero_array_initializer(int *array, int rows);
void retrieve_feature_from_table(double **matrix, int rows, int cols, sqlite3 *db);
void retrieve_label_from_table(int *array, int amount_of_features, sqlite3 *db);
double euclidean_distance(double **matrix, unsigned int k, unsigned int i, unsigned int amount_of_columns);
double cumulative_proximity(double **matrix, unsigned int k, unsigned int amount_of_columns);
double offline_eccentricity(double **matrix, unsigned int amount_of_columns, unsigned int k);
double online_eccentricity(double **matrix, double *mi, double *sigma, unsigned int amount_of_columns, unsigned int k);
int get_amount_of_data(sqlite3 *db);
double m_function(unsigned int k);
double m_function_second_degree(unsigned int k);
double m_function_linear(unsigned int k);
double outlier_condition(double m, unsigned int k);