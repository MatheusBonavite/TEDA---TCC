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

/* DbFunctions Folder */
sqlite3 *either_exists_or_create_table(char *, sqlite3 *);        // CreateTable.c
unsigned int describe_features(sqlite3 *);                        // DescribeFeatures.c
int get_amount_of_data(sqlite3 *);                                // GetAmountOfData.c
void insert_entries_in_table(char *, sqlite3 *);                  // InsertTable.c
void retrieve_feature_from_table(double **, int, int, sqlite3 *); // RetrieveFeature.c
void retrieve_label_from_table(int *, int, sqlite3 *);            // RetrieveLabel.c
/* DbFunctions Folder */

/*MathFunctions Folder*/
void zero_matrix_initializer(double **, int, int);                                                                   // ZeroMatrixInitializer.c
void zero_array_initializer(int *, int);                                                                             // ZeroArrayInitializer.c
double euclidean_distance(double **, unsigned int i, unsigned int j, unsigned int amount_of_columns);                // EuclideanDistance.c
double cumulative_proximity(double **, unsigned int i, unsigned int amount_of, unsigned int amount_of_columns);      // CumulativeProximity.c
double offline_eccentricity(double **, unsigned int amount_of_columns, unsigned int amount_of, unsigned int i);      // OnlineEccentricity.c
double online_eccentricity(double **, double *, double *, double *, unsigned int amount_of_columns, unsigned int k); // OfflineEccentricity.c
double m_function(unsigned int k);                                                                                   // MFunction.c
double m_function_second_degree(unsigned int k);                                                                     // MFunctionSecondDegree.c
double m_function_linear(unsigned int k);                                                                            // MFunctionLinear.c
double outlier_condition(double, unsigned int k);                                                                    // OutlierCondition.c
/*MathFunctions Folder*/