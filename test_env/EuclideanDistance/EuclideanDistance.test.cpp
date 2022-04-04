#define CATCH_CONFIG_MAIN
#include "../catch.hh"

TEST_CASE("This is a test")
{
    REQUIRE(2 + 2 == 3);
}