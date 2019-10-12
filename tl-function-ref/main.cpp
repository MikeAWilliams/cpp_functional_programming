#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"
#include <tl/function_ref.hpp>

#include <functional>
#include <numeric>
#include <vector>

std::vector<int> GetSimpleTestData(const size_t size)
{
   std::vector<int> result(size);
   std::iota(result.begin(), result.end(), 0);
   return result;
}

template<typename function, typename iterator>
void MutateTemplate(iterator begin, iterator end, function mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

template<typename iterator>
void MutateStdFunction(iterator begin, iterator end, std::function<void(int&)> mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

template<typename iterator>
void MutateStdFunctionRef(iterator begin, iterator end, const std::function<void(int&)>& mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

template<typename iterator>
void MutateFunctionRef(iterator begin, iterator end, const tl::function_ref<void(int&)>& mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

TEST_CASE("Performance testing")
{
   auto testData {GetSimpleTestData(100)};
	BENCHMARK("TemplateArg")
	{	
      MutateTemplate(testData.begin(), testData.end(), 
         [](int& item)
         {
            item += 5;
         });
	};

   testData = GetSimpleTestData(100);
	BENCHMARK("StdFunction")
	{	
      MutateStdFunction(testData.begin(), testData.end(), 
         [](int& item)
         {
            item += 5;
         });
	};

   testData = GetSimpleTestData(100);
	BENCHMARK("StdFunctionRef")
	{	
      MutateStdFunctionRef(testData.begin(), testData.end(), 
         [](int& item)
         {
            item += 5;
         });
   };

   testData = GetSimpleTestData(100);
	BENCHMARK("FunctionRef")
	{	
      MutateFunctionRef(testData.begin(), testData.end(), 
         [](int& item)
         {
            item += 5;
         });
   };
}