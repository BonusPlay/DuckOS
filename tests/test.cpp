#include <catch2/catch_test_macros.hpp>
#include <dstd/cstdlib.hpp>

TEST_CASE( "Absolute value works", "[abs]" ) {
    REQUIRE( dstd::abs(1) == 1 );
    REQUIRE( dstd::abs(0) == 0 );
    REQUIRE( dstd::abs(-1) == 1 );
}
