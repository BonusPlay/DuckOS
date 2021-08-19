#include <catch2/catch_test_macros.hpp>
#include <dstd/cstring.hpp>

TEST_CASE( "strlen", "[cstring]" ) {
    const char* src = "Hello There";

    REQUIRE( dstd::strlen(src) == 11 );
}

TEST_CASE( "strcmp", "[cstring]" ) {
    REQUIRE( dstd::strcmp("Hello", "Hello") == 0 );
    REQUIRE( dstd::strcmp("Hello", "Helloooo") == -1 );
    REQUIRE( dstd::strcmp("abc", "cba") == -1 );
    REQUIRE( dstd::strcmp("cba", "abc") == 1 );
    REQUIRE( dstd::strcmp("ooooo", "oooooooooo") == -1) ;
    REQUIRE( dstd::strcmp("", "") == 0 );
    REQUIRE( dstd::strcmp("", "a") == -1 );
    REQUIRE( dstd::strcmp("a", "") == 1 );
}
