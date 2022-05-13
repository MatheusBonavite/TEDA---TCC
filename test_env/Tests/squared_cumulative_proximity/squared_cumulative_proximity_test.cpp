#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include "./squared_cumulative_proximity_header.h"
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

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 0, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 3121.84) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 1, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 507.44) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 2, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 367.36) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 3, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 779.20) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 4, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 424.24) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 5, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 587.44) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 6, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 720.64) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 7, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 379.84) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 8, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 366.64) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 9, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 865.84) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 10, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 741.04) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 11, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 392.96) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 12, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 565.76) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 13, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 445.36) == true);
}

TEST_CASE("Two dimensional cumulative proximity")
{
    TestClass T;
    T.to_test = test_2d;

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 0, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 1388.08) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 1, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 702.24) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 2, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 357.04) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 3, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 401.44) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 4, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 467.44) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 5, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 661.24) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 6, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 540.28) == true);
}

TEST_CASE("Three dimensional cumulative proximity")
{
    TestClass T;
    T.to_test = test_3d;

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 0, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 611.08) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 1, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 332.36) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 2, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 251.64) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 3, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 735.72) == true);
}

TEST_CASE("Four dimensional cumulative proximity")
{
    TestClass T;
    T.to_test = test_4d;

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 0, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 487.88) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 1, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 320.84) == true);

    REQUIRE(T.check_two_numbers(squared_cumulative_proximity(T.to_test, 2, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 391.44) == true);
}