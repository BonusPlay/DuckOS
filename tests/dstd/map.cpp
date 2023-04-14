#include <catch2/catch_test_macros.hpp>
#include <dstd/map.hpp>

TEST_CASE("insert", "[map]") {
    dstd::Map<int, int> a{};
    a.insert(1, 1);
}

TEST_CASE("get", "[map]") {
    dstd::Map<int, int> a{};
    a.insert(1, 1);
    const auto b = a[1];

    CHECK( b );
    CHECK( *b == 1 );
}

TEST_CASE("get error", "[map]") {
    dstd::Map<int, int> a{};

    CHECK( !(a[1]) );
}
