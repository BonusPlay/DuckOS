#include <catch2/catch_test_macros.hpp>
#include <dstd/array.hpp>

TEST_CASE("size", "[array]") {
    dstd::Array<int, 5> a{};
    CHECK(a.size() == 5);
}

TEST_CASE("in-place create", "[array]") {
    dstd::Array<int, 5> a{1,2,3,4,5};
}

TEST_CASE("operator[] const", "[array]") {
    dstd::Array<int, 5> a{1,2,3,4,5};
    CHECK(a[3] == 4);
}

TEST_CASE("operator[]", "[array]") {
    dstd::Array<int, 5> a{1,2,3,4,5};
    a[3] = 7;
    CHECK(a[3] == 7);
}
