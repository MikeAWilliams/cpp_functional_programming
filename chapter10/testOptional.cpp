#include "catch2/catch.hpp"

#include <optional>

#include "optional_functional.h"
#include "testFunctions.h"

TEST_CASE("test transrom", "[optional]")
{
   auto resultWithEmpty = transform(std::optional<double>{}, Add3);
   REQUIRE_FALSE(resultWithEmpty);

   std::optional<double> optional2 { 2.0 };
   auto resultWithTwo = transform(optional2, Add3);
   REQUIRE(resultWithTwo);
   REQUIRE(resultWithTwo.value() == 5.0);
}

TEST_CASE("test mbind", "[optional]")
{
   auto fourResult {mbind(std::optional<int>{4}, Half)};
   REQUIRE(fourResult);
   REQUIRE(fourResult.value() == 2);

   auto threeResult {mbind(std::optional<int>{3}, Half)};
   REQUIRE_FALSE(threeResult);
}

TEST_CASE("test mbind chain", "[optional]")
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

TEST_CASE("simulate real monad use", "[optional]")
{
   auto worker_errorConfig {mbind(GetConfiguration(true, 1), GetDoesWork)};
   REQUIRE_FALSE(worker_errorConfig);

   auto worker_errorSearchDepth {mbind(GetConfiguration(false, -8), GetDoesWork)};
   REQUIRE_FALSE(worker_errorSearchDepth);

   auto worker {mbind(GetConfiguration(false, 1), GetDoesWork)};
   REQUIRE(worker);
}