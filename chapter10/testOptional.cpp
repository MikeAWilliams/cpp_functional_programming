#include "catch2/catch.hpp"

#include <optional>

#include "optional_functional.h"

double Add3(double value)
{
   return value + 3;
}

TEST_CASE("test transrom", "[optional_scratch]")
{
   auto resultWithEmpty = transform(std::optional<double>{}, Add3);
   REQUIRE_FALSE(resultWithEmpty);

   std::optional<double> optional2 { 2.0 };
   auto resultWithTwo = transform(optional2, Add3);
   REQUIRE(resultWithTwo);
   REQUIRE(resultWithTwo.value() == 5.0);
}

bool IsEven(int value)
{
   return value % 2 == 0;
}

TEST_CASE("IsEven", "[optional_scratch]")
{
   REQUIRE(IsEven(4));
   REQUIRE(IsEven(0));
   REQUIRE_FALSE(IsEven(3));
}

std::optional<int> Half(int value)
{
   if(IsEven(value))
   {
      return value / 2;
   }
   return {};
}

TEST_CASE("half", "[optional_scratch]")
{
  auto fourResult {Half(4)};
  REQUIRE(fourResult);
  REQUIRE(fourResult.value() == 2);

  auto threeResult {Half(3)};
  REQUIRE_FALSE(threeResult);
}

TEST_CASE("test mbind", "[optional_scratch]")
{
   auto fourResult {mbind(std::optional<int>{4}, Half)};
   REQUIRE(fourResult);
   REQUIRE(fourResult.value() == 2);

   auto threeResult {mbind(std::optional<int>{3}, Half)};
   REQUIRE_FALSE(threeResult);
}

std::optional<int> AddThreeToOddNumbers(int value)
{
   if(!IsEven(value))
   {
      return 3 + value;
   }
   return {};
}

TEST_CASE("test AddThreeToOddNumbers", "[optional_scratch]")
{
   auto threeResult {AddThreeToOddNumbers(3)};
   REQUIRE(threeResult);
   REQUIRE(threeResult.value() == 6);

   auto twoResult {AddThreeToOddNumbers(2)};
   REQUIRE_FALSE(twoResult);
}


TEST_CASE("test mbind chain", "[optional_scratch]")
{
   auto sixResult {mbind(Half(6), AddThreeToOddNumbers)};
   REQUIRE(sixResult);
   REQUIRE(6 == sixResult.value());

   auto sevenResult {mbind(Half(7), AddThreeToOddNumbers)};
   REQUIRE_FALSE(sevenResult);

   auto eightResult {mbind(Half(8), AddThreeToOddNumbers)};
   REQUIRE_FALSE(eightResult);

   auto eightResult2mbindes {mbind(mbind(std::make_optional(8), Half), AddThreeToOddNumbers)};
   REQUIRE_FALSE(eightResult2mbindes);

   auto sixResult2mbindes {mbind(mbind(std::make_optional(6), Half), AddThreeToOddNumbers)};
   REQUIRE(sixResult2mbindes);
   REQUIRE(sixResult2mbindes.value() == 6);
}