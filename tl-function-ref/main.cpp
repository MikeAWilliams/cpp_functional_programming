#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"
#include <tl/function_ref.hpp>

#include <numeric>
#include <vector>

bool f_called = false;
void f(){f_called=true;}

TEST_CASE("first")
{
   tl::function_ref<void(void)> fr = f;
   fr();
   REQUIRE(f_called);
}

std::vector<int> GetSimpleTestData(const size_t size)
{
   std::vector<int> result(size);
   std::iota(result.begin(), result.end(), 0);
   return result;
}

void RunRequirePlusFive(const std::vector<int>& testData)
{
   int expectecd {5};
   for(const auto & item : testData)
   {
      REQUIRE(expectecd == item);
      ++expectecd;
   }
}

template<typename function, typename iterator>
void MutateTemplate(iterator begin, iterator end, function mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

TEST_CASE("MutateTemplate")
{
   auto testData {GetSimpleTestData(10)};

   MutateTemplate(testData.begin(), testData.end(), 
      [](int& item)
      {
         item += 5;
      }); 

   RunRequirePlusFive(testData);
}
