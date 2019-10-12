#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"
#include <tl/function_ref.hpp>

#include <functional>
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

template<typename iterator>
void MutateStdFunction(iterator begin, iterator end, std::function<void(int&)> mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

TEST_CASE("MutateStdFunction")
{
   auto testData {GetSimpleTestData(10)};

   MutateStdFunction(testData.begin(), testData.end(), 
      [](int& item)
      {
         item += 5;
      }); 

   RunRequirePlusFive(testData);
}

template<typename iterator>
void MutateStdFunctionRef(iterator begin, iterator end, const std::function<void(int&)>& mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

TEST_CASE("MutateStdFunctionRef")
{
   auto testData {GetSimpleTestData(10)};

   MutateStdFunctionRef(testData.begin(), testData.end(), 
      [](int& item)
      {
         item += 5;
      }); 

   RunRequirePlusFive(testData);
}

template<typename iterator>
void MutateFunctionRef(iterator begin, iterator end, const tl::function_ref<void(int&)>& mutate)
{
   for(;begin != end; ++begin)
   {
      mutate(*begin);
   }
}

TEST_CASE("MutateFunctionRef")
{
   auto testData {GetSimpleTestData(10)};

   MutateFunctionRef(testData.begin(), testData.end(), 
      [](int& item)
      {
         item += 5;
      }); 

   RunRequirePlusFive(testData);
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