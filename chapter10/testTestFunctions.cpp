#include "catch2/catch.hpp"

#include <optional>

#include "testFunctions.h"

TEST_CASE("IsEven", "[testTestFunctions]")
{
   REQUIRE(IsEven(4));
   REQUIRE(IsEven(0));
   REQUIRE_FALSE(IsEven(3));
}

TEST_CASE("half", "[testTestFunctions]")
{
  auto fourResult {Half(4)};
  REQUIRE(fourResult);
  REQUIRE(fourResult.value() == 2);

  auto threeResult {Half(3)};
  REQUIRE_FALSE(threeResult);
}

TEST_CASE("test AddThreeToOddNumbers", "[testTestFunctions]")
{
   auto threeResult {AddThreeToOddNumbers(3)};
   REQUIRE(threeResult);
   REQUIRE(threeResult.value() == 6);

   auto twoResult {AddThreeToOddNumbers(2)};
   REQUIRE_FALSE(twoResult);
}