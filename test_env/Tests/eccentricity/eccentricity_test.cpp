#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include "./eccentricity_header.h"
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

TEST_CASE("One dimensional offline eccentricity")
{
    TestClass T;
    T.to_test = test_1d;

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 0, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.37566947207345064) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 1, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.10864575363427695) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 2, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.10405508798775821) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 3, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.1782708492731446) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 4, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.12471308339709257) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 5, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.1185921958684009) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 6, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.17061973986228002) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 7, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.098699311400153) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 8, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.1025248661055853) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 9, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.1599081866870696) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 10, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.14154552410099464) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 11, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.098699311400153) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 12, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.11553175210405507) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 13, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.1025248661055853) == true);
}

TEST_CASE("Two dimensional offline eccentricity")
{
    TestClass T;
    T.to_test = test_2d;

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 0, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.4533083423754153) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 1, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.3195081323809366) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 2, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.2158198643435594) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 3, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.24312601260907624) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 4, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.24342380590053667) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 5, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.2777686168329104) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 6, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.24704522555756528) == true);
}

TEST_CASE("Three dimensional offline eccentricity")
{
    TestClass T;
    T.to_test = test_3d;

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 0, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.5685027210889533) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 1, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.4178878441747299) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 2, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.36855206418623626) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 3, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.6450573705500803) == true);
}

TEST_CASE("Four dimensional offline eccentricity")
{
    TestClass T;
    T.to_test = test_4d;

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 0, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 0.746272226166855) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 1, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 0.5997232108556381) == true);

    REQUIRE(T.check_two_numbers(eccentricity(T.to_test, 2, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 0.6540045629775069) == true);
}