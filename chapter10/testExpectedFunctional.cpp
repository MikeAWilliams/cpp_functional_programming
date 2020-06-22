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

const std::string ODD_ERROR_MESSAGE {"The value was odd"};
const std::string EVEN_ERROR_MESSAGE {"The value was even"};

TEST_CASE("test mbind expected", "[expected]")
{
   auto fourResult {mbind(tl::expected<int, std::string>{4}, HalfE)};
   REQUIRE(fourResult);
   REQUIRE(fourResult.value() == 2);

   auto threeResult {mbind(tl::expected<int, std::string>{3}, HalfE)};
   REQUIRE_FALSE(threeResult);
   REQUIRE(ODD_ERROR_MESSAGE == threeResult.error());
}

TEST_CASE("test mbind chain expected", "[expected]")
{
   auto sixResult {mbind(HalfE(6), AddThreeToOddNumbersE)};
   REQUIRE(sixResult);
   REQUIRE(6 == sixResult.value());

   auto sevenResult {mbind(HalfE(7), AddThreeToOddNumbersE)};
   REQUIRE_FALSE(sevenResult);
   REQUIRE(ODD_ERROR_MESSAGE == sevenResult.error());

   auto eightResult {mbind(HalfE(8), AddThreeToOddNumbersE)};
   REQUIRE_FALSE(eightResult);
   REQUIRE(EVEN_ERROR_MESSAGE == eightResult.error());

   auto eightResult2mbindes {mbind(mbind(tl::expected<int, std::string>{8}, HalfE), AddThreeToOddNumbersE)};
   REQUIRE_FALSE(eightResult2mbindes);
   REQUIRE(EVEN_ERROR_MESSAGE == eightResult2mbindes.error());

   auto sixResult2mbindes {mbind(mbind(tl::expected<int, std::string>{6}, HalfE), AddThreeToOddNumbersE)};
   REQUIRE(sixResult2mbindes);
   REQUIRE(sixResult2mbindes.value() == 6);
}

TEST_CASE("simulate real monad use expected", "[expected]")
{
   const std::string errorInConfig {"The config is really bad"};
   auto worker_errorConfig {mbind(GetConfigurationE(errorInConfig, 1), GetDoesWorkE)};
   REQUIRE_FALSE(worker_errorConfig);
   REQUIRE(errorInConfig == worker_errorConfig.error());

   auto worker_errorSearchDepth {mbind(GetConfigurationE("", -8), GetDoesWorkE)};
   REQUIRE_FALSE(worker_errorSearchDepth);
   REQUIRE(worker_errorSearchDepth.error().size() > 0);

   auto worker {mbind(GetConfigurationE("", 1), GetDoesWorkE)};
   REQUIRE(worker);
}