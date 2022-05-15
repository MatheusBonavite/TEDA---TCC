#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include "./recursive_eccentricity_test.h"
#include <math.h>
#include <stdlib.h>

#define ONE_DIMENSION_ROWS 14
#define ONE_DIMENSION_COLS 1

#define TWO_DIMENSION_ROWS 7
#define TWO_DIMENSION_COLS 2

#define THREE_DIMENSION_ROWS 4
#define THREE_DIMENSION_COLS 3

#define FOUR_DIMENSION_ROWS 3
#define FOUR_DIMENSION_COLS 4

double test_1d[ONE_DIMENSION_ROWS][ONE_DIMENSION_COLS] = {
    {20.2},
    {3.0},
    {6.4},
    {11.6},
    {8.2},
    {2.2},
    {11.2},
    {5.2},
    {6.2},
    {0.2},
    {1.0},
    {4.8},
    {2.4},
    {3.8}};
double test_2d[TWO_DIMENSION_ROWS][TWO_DIMENSION_COLS] = {
    {20.2, 3.0},
    {6.4, 11.6},
    {8.2, 2.2},
    {11.2, 5.2},
    {6.2, 0.2},
    {1.0, 4.8},
    {2.4, 3.8}};
double test_3d[THREE_DIMENSION_ROWS][THREE_DIMENSION_COLS] = {
    {20.2, 3.0, 6.4},
    {11.6, 8.2, 2.2},
    {11.2, 5.2, 6.2},
    {0.2, 1.0, 4.8}};

double test_4d[FOUR_DIMENSION_ROWS][FOUR_DIMENSION_COLS] = {
    {20.2, 3.0, 6.4, 11.6},
    {8.2, 2.2, 11.2, 5.2},
    {6.2, 0.2, 1.0, 4.8}};
class TestClass
{
public:
    double *to_test;
    bool check_two_numbers(double, double, double);
};

bool TestClass::check_two_numbers(double first_val, double sec_val, double epsilon = 0.00001)
{
    return fabs(first_val - sec_val) < epsilon;
}

TEST_CASE("One dimensional recursive eccentricity")
{
    TestClass T;

    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;
    double *mi_current = (double *)malloc(ONE_DIMENSION_COLS * sizeof(double));

    for (unsigned int i = 0; i < ONE_DIMENSION_ROWS; i++)
    {
        recursive_eccentricity(i, test_1d[i], mi_current, sigma_current, eccentricity, ONE_DIMENSION_COLS);
    }

    REQUIRE(T.check_two_numbers(*eccentricity, 0.08676745635910224) == true);
    free(mi_current);
}

TEST_CASE("Two dimensional recursive eccentricity")
{
    TestClass T;

    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;
    double *mi_current = (double *)malloc(TWO_DIMENSION_COLS * sizeof(double));

    for (unsigned int i = 0; i < TWO_DIMENSION_ROWS; i++)
    {
        recursive_eccentricity(i, test_2d[i], mi_current, sigma_current, eccentricity, TWO_DIMENSION_COLS);
    }

    REQUIRE(T.check_two_numbers(*eccentricity, 0.2391804788213628) == true);
    free(mi_current);
}

TEST_CASE("Three dimensional recursive eccentricity")
{
    TestClass T;

    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;
    double *mi_current = (double *)malloc(THREE_DIMENSION_COLS * sizeof(double));

    for (unsigned int i = 0; i < THREE_DIMENSION_ROWS; i++)
    {
        recursive_eccentricity(i, test_3d[i], mi_current, sigma_current, eccentricity, THREE_DIMENSION_COLS);
    }

    REQUIRE(T.check_two_numbers(*eccentricity, 0.7620882535736483) == true);
    free(mi_current);
}

TEST_CASE("Four dimensional recursive eccentricity")
{
    TestClass T;

    double sigma_current_value = 0.0;
    double eccentricity_value = 1.0;
    double *sigma_current = &sigma_current_value;
    double *eccentricity = &eccentricity_value;
    double *mi_current = (double *)malloc(FOUR_DIMENSION_COLS * sizeof(double));

    for (unsigned int i = 0; i < FOUR_DIMENSION_ROWS; i++)
    {
        recursive_eccentricity(i, test_4d[i], mi_current, sigma_current, eccentricity, FOUR_DIMENSION_COLS);
    }

    REQUIRE(T.check_two_numbers(*eccentricity, 0.6523130249300093) == true);
    free(mi_current);
}