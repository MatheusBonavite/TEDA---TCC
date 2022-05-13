#define CATCH_CONFIG_MAIN
#include "../test_lib/catch.hh"
#include "./squared_eccentricity_header.h"
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

TEST_CASE("One dimensional offline squared eccentricity")
{
    TestClass T;
    T.to_test = test_1d;

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 0, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.6082138403990025) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 1, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.09886221945137157) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 2, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.071571072319202) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 3, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.1518079800498753) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 4, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.08265274314214464) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 5, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.11444825436408979) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 6, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.14039900249376558) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 7, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.07400249376558603) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 8, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.07143079800498753) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 9, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.16868765586034912) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 10, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.1443734413965087) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 11, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.07655860349127182) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 12, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.11022443890274314) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 13, ONE_DIMENSION_ROWS, ONE_DIMENSION_COLS), 0.08676745635910224) == true);
}

TEST_CASE("Two dimensional offline squared eccentricity")
{
    TestClass T;
    T.to_test = test_2d;

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 0, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.6144992208528121) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 1, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.31087972800679986) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 2, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.15806063181753793) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 3, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.17771639042357276) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 4, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.20693440997308404) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 5, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.29272914010483075) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 6, TWO_DIMENSION_ROWS, TWO_DIMENSION_COLS), 0.2391804788213628) == true);
}

TEST_CASE("Three dimensional offline squared eccentricity")
{
    TestClass T;
    T.to_test = test_3d;

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 0, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.6329811477107935) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 1, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.3442718044333955) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 2, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.2606587942821628) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 3, THREE_DIMENSION_ROWS, THREE_DIMENSION_COLS), 0.7620882535736483) == true);
}

TEST_CASE("Four dimensional offline squared eccentricity")
{
    TestClass T;
    T.to_test = test_4d;

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 0, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 0.8130249300093321) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 1, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 0.5346620450606585) == true);

    REQUIRE(T.check_two_numbers(squared_eccentricity(T.to_test, 2, FOUR_DIMENSION_ROWS, FOUR_DIMENSION_COLS), 0.6523130249300093) == true);
}