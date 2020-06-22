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