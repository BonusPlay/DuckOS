#include <catch2/catch_test_macros.hpp>
#include <dstd/string.hpp>

TEST_CASE("to_string", "[string]" ) {
    REQUIRE( dstd::to_string(-42) == "-42"_s );
    REQUIRE( dstd::to_string(123) == "123"_s );
    REQUIRE( dstd::to_string(42) == dstd::String("42") );
}

TEST_CASE("string works", "[string]") {
    dstd::String str("Test string");

    REQUIRE(str.length() == 11);
    REQUIRE(str.empty() == false);
    REQUIRE(str[2] == 's');
}
