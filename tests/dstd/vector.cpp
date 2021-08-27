#include <catch2/catch_test_macros.hpp>
#include <dstd/vector.hpp>

TEST_CASE("vector", "[vector]") {
    dstd::Vector<uint32_t> a;

    REQUIRE( a.capacity() == 0 );
    REQUIRE( a.empty() );
    REQUIRE( a.size() == 0 );

    a.reserve(5);

    REQUIRE( a.capacity() == 5 );
    REQUIRE( a.empty() == true );
    REQUIRE( a.size() == 0 );

    a.push_back(1337);

    REQUIRE( a.capacity() == 5 );
    REQUIRE( a.empty() == false );
    REQUIRE( a.size() == 1 );
}
