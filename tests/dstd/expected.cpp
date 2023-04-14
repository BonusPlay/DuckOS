#include <catch2/catch_test_macros.hpp>
#include <dstd/expected.hpp>
#include <dstd/string.hpp>

TEST_CASE( "value ctor", "[Expected]" ) {
    const auto a = dstd::Expected<int, dstd::String>{1};

    REQUIRE( bool(a) == true );
    REQUIRE( a.has_value() == true );
    REQUIRE( *a == 1 );
}

TEST_CASE( "Unexpected", "[Expected]" ) {
    const auto a = dstd::Unexpected<int, dstd::String>("failed");

    REQUIRE( bool(a) == false );
    REQUIRE( a.has_value() == false );
    REQUIRE( a.error() == dstd::String{"failed"} );
}
