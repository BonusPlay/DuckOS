#include <catch2/catch_test_macros.hpp>
#include <dstd/optional.hpp>

TEST_CASE( "Optional empty ctor", "[Optional]" ) {
    const auto a = dstd::Optional<int>{};

    REQUIRE( bool(a) == false );
    REQUIRE( a.has_value() == false );
}

TEST_CASE( "Optional non-empty ctor", "[Optional]" ) {
    const auto a = dstd::Optional<int>{1337};

    REQUIRE( bool(a) == true );
    REQUIRE( a.has_value() == true );
    REQUIRE( *a == 1337 );
}
