#include <catch2/catch_test_macros.hpp>
#include <dstd/cstring.hpp>

TEST_CASE( "to_string", "[string]" ) {
    REQUIRE( std::to_string(-42) == "-42" );
    REQUIRE( std::to_string(123) == "123" );
}
