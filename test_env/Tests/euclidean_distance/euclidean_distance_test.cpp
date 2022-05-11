#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include "./euclidean_header.h"
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

TEST_CASE("One dimensional squared euclidean distance")
{
    TestClass T;
    T.to_test = test_1d;
    T.problem_dimension = 1;

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 1, T.problem_dimension), 17.2) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 2, T.problem_dimension), 13.8) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 5, 10, T.problem_dimension), 1.2) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 3, 13, T.problem_dimension), 7.8) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 7, 8, T.problem_dimension), 1.00) == true);
}

TEST_CASE("Two dimensional squared euclidean distance")
{
    TestClass T;
    T.to_test = test_2d;
    T.problem_dimension = 2;

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 1, T.problem_dimension), 16.260381) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 2, 6, T.problem_dimension), 6.016644) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 5, 6, T.problem_dimension), 1.720465) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 2, 3, T.problem_dimension), 4.242641) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 1, 5, T.problem_dimension), 8.683317) == true);
}

TEST_CASE("Three dimensional squared euclidean distance")
{
    TestClass T;
    T.to_test = test_3d;
    T.problem_dimension = 3;

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 1, T.problem_dimension), 10.892199) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 1, 2, T.problem_dimension), 5.015974) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 2, 3, T.problem_dimension), 11.857487) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 3, T.problem_dimension), 20.163333) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 2, T.problem_dimension), 9.267146) == true);
}