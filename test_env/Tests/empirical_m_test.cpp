#define CATCH_CONFIG_MAIN
#include "./test_lib/catch.hh"
#include <math.h>
#include <stdlib.h>
#include "./header/global_header.h"

TEST_CASE("Saturation point for empirical m function close to 3.0")
{
    int k = 1000;
    REQUIRE(fabs(empirical_m(k) - 3.0) < 0.0055);
}

TEST_CASE("Value for m when k == 2")
{
    int k = 2;
    REQUIRE(fabs((empirical_m(k) - 1.0047704492766198)) < 0.00055);
}