#include <catch2/catch_test_macros.hpp>
#include <dstd/map.hpp>

TEST_CASE("insert", "[map]") {
    dstd::Map<int, int> a{};
    a[1] = 1;

    CHECK(a[1] == 1);
}
