#include "mrange.h"

#include <functional>
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

TEST_CASE("test FilterIterator", "[mrange]")
{
   std::vector<int> container {4, 7, -22};
   mrange::FilterIterator<std::vector<int>::iterator, std::function<bool(int)>> 
      testObject {container.begin(), container.end(), [](int item)
      {
         return item < 5;
      }};

   REQUIRE(4 == *testObject);
   ++testObject;
   REQUIRE(-22 == *testObject);
}