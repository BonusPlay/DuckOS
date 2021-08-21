#include <catch2/catch_test_macros.hpp>
#include <dstd/cstring.hpp>

TEST_CASE( "strlen", "[cstring]" ) {
    const char* src = "Hello There";

    CHECK( dstd::strlen(src) == 11 );
}

TEST_CASE( "strcmp", "[cstring]" ) {
    CHECK( dstd::strcmp("Hello", "Hello") == 0 );
    CHECK( dstd::strcmp("Hello", "Helloooo") == -1 );
    CHECK( dstd::strcmp("abc", "cba") == -1 );
    CHECK( dstd::strcmp("cba", "abc") == 1 );
    CHECK( dstd::strcmp("ooooo", "oooooooooo") == -1) ;
    CHECK( dstd::strcmp("", "") == 0 );
    CHECK( dstd::strcmp("", "a") == -1 );
    CHECK( dstd::strcmp("a", "") == 1 );
}

TEST_CASE( "memset", "[memset]" ) {
    char src[24] = "Hello There";

    dstd::memset(&src, 'A', 6);

    CHECK( src == "AAAAAAThere" );
}
