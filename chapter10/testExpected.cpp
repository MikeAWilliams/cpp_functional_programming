#include "catch2/catch.hpp"
#include "tl/expected.hpp"

#include <string>

TEST_CASE("stuff", "[expected_scratch]")
{
   tl::expected<int, std::string> testObject42{42};
   REQUIRE(testObject42); 
   REQUIRE(42 == *testObject42); 

   const std::string errorString {"The value is wrong"};
   tl::expected<int, std::string> testObjectError{tl::make_unexpected(errorString)};
   REQUIRE_FALSE(testObjectError);
   REQUIRE(errorString == testObjectError.error());
}

