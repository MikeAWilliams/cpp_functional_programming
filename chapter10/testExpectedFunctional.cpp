#include "catch2/catch.hpp"

#include "tl/expected.hpp"

#include "expected_functional.h"
#include "testFunctions.h"

#include <string>

TEST_CASE("test transrom expected", "[expected]")
{
   const std::string errorMessage {"It is all wrong"};
   tl::expected<double, std::string> error {tl::make_unexpected(errorMessage)};
   REQUIRE_FALSE(error);
   REQUIRE(errorMessage == error.error());

   tl::expected<double, std::string> expected2 {2.0};
   auto resultWithTwo = transform(expected2, Add3);
   REQUIRE(resultWithTwo);
   REQUIRE(*resultWithTwo == 5.0);
}

TEST_CASE("test mbind expected", "[expected]")
{
   auto fourResult {mbind(tl::expected<int, std::string>{4}, HalfE)};
   REQUIRE(fourResult);
   REQUIRE(fourResult.value() == 2);

   auto threeResult {mbind(tl::expected<int, std::string>{3}, HalfE)};
   REQUIRE_FALSE(threeResult);
   REQUIRE("The value was odd" == threeResult.error());
}

//TEST_CASE("test mbind chain expected", "[expected]")
//{
   //auto sixResult {mbind(Half(6), AddThreeToOddNumbers)};
   //REQUIRE(sixResult);
   //REQUIRE(6 == sixResult.value());

   //auto sevenResult {mbind(Half(7), AddThreeToOddNumbers)};
   //REQUIRE_FALSE(sevenResult);

   //auto eightResult {mbind(Half(8), AddThreeToOddNumbers)};
   //REQUIRE_FALSE(eightResult);

   //auto eightResult2mbindes {mbind(mbind(std::make_optional(8), Half), AddThreeToOddNumbers)};
   //REQUIRE_FALSE(eightResult2mbindes);

   //auto sixResult2mbindes {mbind(mbind(std::make_optional(6), Half), AddThreeToOddNumbers)};
   //REQUIRE(sixResult2mbindes);
   //REQUIRE(sixResult2mbindes.value() == 6);
//}

//TEST_CASE("simulate real monad use expected", "[expected]")
//{
   //auto worker_errorConfig {mbind(GetConfiguration(true, 1), GetDoesWork)};
   //REQUIRE_FALSE(worker_errorConfig);

   //auto worker_errorSearchDepth {mbind(GetConfiguration(false, -8), GetDoesWork)};
   //REQUIRE_FALSE(worker_errorSearchDepth);

   //auto worker {mbind(GetConfiguration(false, 1), GetDoesWork)};
   //REQUIRE(worker);
//}