#include <catch2/catch_test_macros.hpp>
#include <dstd/unique_ptr.hpp>

TEST_CASE("constructor", "[unique_ptr]") {
    dstd::UniquePtr<int> a = dstd::UniquePtr(new int);

    REQUIRE(a);
    *a = 5;
}
