#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include "./cumulative_proximity_header.h"
#include <math.h>
#include <stdlib.h>

#define ONE_DIMENSION_ROWS 14
#define ONE_DIMENSION_COLS 1

#define TWO_DIMENSION_ROWS 7
#define TWO_DIMENSION_COLS 2

#define THREE_DIMENSION_ROWS 4
#define THREE_DIMENSION_COLS 3

double test_1d[ONE_DIMENSION_ROWS * ONE_DIMENSION_COLS] = {
    20.2,
    3.0,
    6.4,
    11.6,
    8.2,
    2.2,
    11.2,
    5.2,
    6.2,
    0.2,
    1.0,
    4.8,
    2.4,
    3.8};
double test_2d[TWO_DIMENSION_ROWS * TWO_DIMENSION_COLS] = {
    20.2, 3.0,
    6.4, 11.6,
    8.2, 2.2,
    11.2, 5.2,
    6.2, 0.2,
    1.0, 4.8,
    2.4, 3.8};
double test_3d[THREE_DIMENSION_ROWS * THREE_DIMENSION_COLS] = {
    20.2, 3.0, 6.4,
    11.6, 8.2, 2.2,
    11.2, 5.2, 6.2,
    0.2, 1.0, 4.8};

class TestClass
{
public:
    double *to_test;
    unsigned int problem_dimension;
    bool check_two_numbers(double, double, double);
};

bool TestClass::check_two_numbers(double first_val, double sec_val, double epsilon = 0.00001)
{
    return fabs(first_val - sec_val) < epsilon;
}
