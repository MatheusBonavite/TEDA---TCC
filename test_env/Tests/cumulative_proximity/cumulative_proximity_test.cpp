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

TEST_CASE("One dimensional cumulative proximity")
{
    TestClass T;
    T.to_test = test_1d;

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 0, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 196.4) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 1, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 56.8) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 2, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 54.4) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 3, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 93.2) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 4, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 65.2) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 5, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 62.0) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 6, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 89.2) == true);
}

TEST_CASE("Two dimensional cumulative proximity")
{
    TestClass T;
    T.to_test = test_2d;

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 0, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 88.931419) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 1, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 62.682084) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 2, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 42.340202) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 3, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 47.6972058) == true);
}

TEST_CASE("Four dimensional cumulative proximity")
{
    TestClass T;
    T.to_test = test_4d;

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 0, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 31.154852) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 1, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 25.036826) == true);

    REQUIRE(T.check_two_numbers(cumulative_proximity(T.to_test, 2, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 27.302926) == true);
}