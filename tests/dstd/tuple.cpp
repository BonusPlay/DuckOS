#include <catch2/catch_test_macros.hpp>
#include <dstd/tuple.hpp>
#include <dstd/string.hpp>

TEST_CASE("get", "[tuple]") {
    dstd::Tuple<int, dstd::String> a{2137, "abcd"};
    CHECK( a.get<0>() == 2137 );
    //CHECK( a.get<1>() == dstd::String{"abcd"} );
}
