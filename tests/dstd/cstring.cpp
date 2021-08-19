#include <catch2/catch_test_macros.hpp>
#include <dstd/cstring.hpp>

TEST_CASE( "strlen", "[cstring]" ) {
    const char* src = "Hello There";

    REQUIRE( dstd::strlen(src) == 11 );
}
