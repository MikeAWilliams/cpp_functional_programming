#include "catch2/catch.hpp"
#include "immer/array.hpp"

TEST_CASE("first array test", "[immer]")
{
    auto v1 = immer::array<int>{1};
    auto v2 = v1.push_back(8);

    REQUIRE((v1 == immer::array<int>{1}));
    REQUIRE((v2 == immer::array<int>{1, 8}));
}