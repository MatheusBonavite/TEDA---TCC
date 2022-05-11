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

#define FOUR_DIMENSION_ROWS 3
#define FOUR_DIMENSION_COLS 4

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

double test_4d[FOUR_DIMENSION_ROWS * FOUR_DIMENSION_COLS] = {
    20.2, 3.0, 6.4, 11.6,
    8.2, 2.2, 11.2, 5.2,
    6.2, 0.2, 1.0, 4.8};

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

TEST_CASE("One dimensional euclidean distance")
{
    TestClass T;
    T.to_test = test_1d;

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 1, ONE_DIMENSION_COLS), 17.2) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 2, ONE_DIMENSION_COLS), 13.8) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 5, 10, ONE_DIMENSION_COLS), 1.2) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 3, 13, ONE_DIMENSION_COLS), 7.8) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 7, 8, ONE_DIMENSION_COLS), 1.00) == true);
}

TEST_CASE("Two dimensional euclidean distance")
{
    TestClass T;
    T.to_test = test_2d;

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 1, TWO_DIMENSION_COLS), 16.260381) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 2, 6, TWO_DIMENSION_COLS), 6.016644) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 5, 6, TWO_DIMENSION_COLS), 1.720465) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 2, 3, TWO_DIMENSION_COLS), 4.242641) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 1, 5, TWO_DIMENSION_COLS), 8.683317) == true);
}

TEST_CASE("Three dimensional euclidean distance")
{
    TestClass T;
    T.to_test = test_3d;

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 1, THREE_DIMENSION_COLS), 10.892199) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 1, 2, THREE_DIMENSION_COLS), 5.015974) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 2, 3, THREE_DIMENSION_COLS), 11.857487) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 3, THREE_DIMENSION_COLS), 20.163333) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 2, THREE_DIMENSION_COLS), 9.267146) == true);
}

TEST_CASE("Four dimensional euclidean distance")
{
    TestClass T;
    T.to_test = test_4d;

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 1, FOUR_DIMENSION_COLS), 14.444376) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 1, 2, FOUR_DIMENSION_COLS), 10.592450) == true);

    REQUIRE(T.check_two_numbers(euclidean_distance(T.to_test, 0, 2, FOUR_DIMENSION_COLS), 16.710476) == true);
}