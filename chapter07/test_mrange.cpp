#include "mrange.h"

#include <iostream>
#include <vector>

#include "catch2/catch.hpp"

TEST_CASE("range constructor", "[mrange]")
{
   std::vector<int> container {4, 7, -22};
   mrange::Range<std::vector<int>> testObject{container};

   REQUIRE(container.begin() == testObject.begin);
   REQUIRE(container.end() == testObject.end);
}

TEST_CASE("test MakeRange", "[mrange]")
{
   std::vector<int> container {4, 7, -22};
   auto testObject {mrange::MakeRange(container)};

   REQUIRE(container.begin() == testObject.begin);
   REQUIRE(container.end() == testObject.end);
}

TEST_CASE("test Transform", "[mrange]")
{
   std::vector<int> container {4, 7, -22};
   auto testObject {mrange::MakeRange(container)};

   mrange::Transform(testObject, [](int i) 
      {
         return i + 1;
      });

   REQUIRE(5 == container[0]);
   REQUIRE(8 == container[1]);
   REQUIRE(-21 == container[2]);
}