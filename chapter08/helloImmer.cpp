#include "catch2/catch.hpp"
#include "immer/array.hpp"
#include "range/v3/all.hpp"

TEST_CASE("first array test", "[immer]")
{
    auto v1 = immer::array<int>{1};
    auto v2 = v1.push_back(8);

    REQUIRE((v1 == immer::array<int>{1}));
    REQUIRE((v2 == immer::array<int>{1, 8}));
}

auto is_six = [](int i) { return i == 6; };

TEST_CASE("range example with immer array", "[immer]")
{
    immer::array<int> v{6, 2, 3, 4, 5, 6};
 
    REQUIRE(ranges::any_of(v, is_six));
    REQUIRE_FALSE(ranges::all_of(v, is_six));
    REQUIRE_FALSE(ranges::none_of(v, is_six));
}
