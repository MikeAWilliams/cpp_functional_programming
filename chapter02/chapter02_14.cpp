#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/catch.hpp"

struct Person
{
	std::string Name;
	bool IsFemale;
};

static bool IsFemale(const Person& person)
{
	return person.IsFemale;
}

static bool IsNotFemale(const Person& person)
{
	return !person.IsFemale;
}

static std::string Name(const Person& person)
{
	return person.Name;
}

// TODO I am not happy specifying the iterator in the template list. I think it should be std::vector<inputType>::const_iterator
// however that doesn't compile right now and I am moving on
template<typename resultType, typename inputType, typename iteratorType>
std::vector<resultType> FilterTransformTailRecursion(
	iteratorType dataBegin,
	iteratorType dataEnd,
	std::function<bool(const inputType&)> filter,
	std::function<resultType(const inputType&)> transform,
	std::vector<resultType> previousResult)
{
	if(dataBegin == dataEnd)
	{
		return previousResult;
	}
	
	const auto head = *dataBegin;
	if(filter(head))
	{
		previousResult.push_back(transform(head));
	}
	return FilterTransformTailRecursion(dataBegin + 1, dataEnd, filter, transform, std::move(previousResult));
}

static std::vector<std::string> GetNamesOfFemalesTailRecursion(const std::vector<Person>& people)
{
	return FilterTransformTailRecursion<std::string, Person, std::vector<Person>::const_iterator>(people.cbegin(), people.cend(), 
	    [](const Person& p)
		{
			return IsFemale(p);
		},
		[](const Person& p)
		{
			return Name(p); 
		}, {});
}

template<typename resultType, typename inputType, typename iteratorType>
std::vector<resultType> FilterTransformNoTailRecursion(
	iteratorType dataBegin,
	iteratorType dataEnd,
	std::function<bool(const inputType&)> filter,
	std::function<resultType(const inputType&)> transform,
	std::vector<resultType> previousResult)
{
	if(dataBegin == dataEnd)
	{
		return previousResult;
	}
	
	const auto head = *dataBegin;
	auto result {FilterTransformTailRecursion(dataBegin + 1, dataEnd, filter, transform, std::move(previousResult))};

	if(filter(head))
	{
		result.push_back(transform(head));
	}
	return result;
}

static std::vector<std::string> GetNamesOfFemalesNoTailRecursion(const std::vector<Person>& people)
{
	return FilterTransformNoTailRecursion<std::string, Person, std::vector<Person>::const_iterator>(people.cbegin(), people.cend(), 
	    [](const Person& p)
		{
			return IsFemale(p);
		},
		[](const Person& p)
		{
			return Name(p); 
		}, {});
}

template<typename resultType, typename inputType, typename iteratorType>
std::vector<resultType> FilterTransformLoop(
	iteratorType dataBegin,
	iteratorType dataEnd,
	std::function<bool(const inputType&)> filter,
	std::function<resultType(const inputType&)> transform)
{
	std::vector<resultType> result;
	for(; dataBegin != dataEnd; ++dataBegin)
	{
		if(filter(*dataBegin))
		{
			result.emplace_back(transform(*dataBegin));
		}
	}
	return result;
}

static std::vector<std::string> GetNamesOfFemalesLoop(const std::vector<Person>& people)
{
	return FilterTransformLoop<std::string, Person, std::vector<Person>::const_iterator>(people.cbegin(), people.cend(), 
	    [](const Person& p)
		{
			return IsFemale(p);
		},
		[](const Person& p)
		{
			return Name(p); 
		});
}

// Testing functions
template<typename t>
static void RequireVectorsMatchUnordered(std::vector<t>& first, std::vector<t>& second)
{
	REQUIRE(first.size() == second.size());
	std::sort(first.begin(), first.end());
	std::sort(second.begin(), second.end());
	REQUIRE(first == second);
}

static void RunTest(std::function<std::vector<std::string>(const std::vector<Person>&)> toTest, 
	const std::vector<Person>& input, std::vector<std::string>& expectedResult)
{
	auto result {toTest(input)};
	RequireVectorsMatchUnordered(expectedResult, result);
}

static void RunTestMixed(std::function<std::vector<std::string>(const std::vector<Person>&)> toTest)
{
	std::vector<Person> input {{"Bob", false}, {"Susan", true}, {"Joe", false}, {"Stephanie", true}};
	std::vector<std::string> expectedResult {"Stephanie", "Susan"};
	
	RunTest(toTest, input, expectedResult);
}

static void RunTestAllMale(std::function<std::vector<std::string>(const std::vector<Person>&)> toTest)
{
	std::vector<Person> input {{"Bob", false}, {"Susan", false}, {"Joe", false}, {"Stephanie", false}};
	std::vector<std::string> expectedResult {};
	
	RunTest(toTest, input, expectedResult);
}

static void RunTestAllFemale(std::function<std::vector<std::string>(const std::vector<Person>&)> toTest)
{
	std::vector<Person> input {{"Bob", true}, {"Susan", true}, {"Joe", true}, {"Stephanie", true}};
	std::vector<std::string> expectedResult {"Bob", "Joe", "Susan", "Stephanie"};

	RunTest(toTest, input, expectedResult);
}

// prove they work for small sets
TEST_CASE("GetNamesOfFemalesMixed_TailRecursion")
{
	RunTestMixed(GetNamesOfFemalesTailRecursion);
}

TEST_CASE("GetNamesOfFemalesAllMale_TailRecursion")
{
	RunTestAllMale(GetNamesOfFemalesTailRecursion);
}

TEST_CASE("GetNamesOfFemalesAllFemale_TailRecursion")
{
	RunTestAllFemale(GetNamesOfFemalesTailRecursion);
}

TEST_CASE("GetNamesOfFemalesMixed_NoTailRecursion")
{
	RunTestMixed(GetNamesOfFemalesNoTailRecursion);
}

TEST_CASE("GetNamesOfFemalesAllMale_NoTailRecursion")
{
	RunTestAllMale(GetNamesOfFemalesNoTailRecursion);
}

TEST_CASE("GetNamesOfFemalesAllFemale_NoTailRecursion")
{
	RunTestAllFemale(GetNamesOfFemalesNoTailRecursion);
}

// run large set for performance testing
std::vector<Person> GenerateLargeTestSet()
{
	const size_t input_size {10'000};
	std::vector<Person> result{input_size};
	
	bool female {true};
	size_t i {0};
	for(auto & person : result)
	{
		person.Name = std::to_string(i);
		person.IsFemale = female;
		female = !female;
		++i;
	}
	
	return result;
}


TEST_CASE("performance testing")
{
	auto set {GenerateLargeTestSet()};
	BENCHMARK("loop")
	{	
		GetNamesOfFemalesLoop(set);
	};
	set = GenerateLargeTestSet();
	BENCHMARK("tail recursion")
	{	
		GetNamesOfFemalesTailRecursion(set);
	};
	set = GenerateLargeTestSet();
	BENCHMARK("no tail recursion")
	{
		GetNamesOfFemalesNoTailRecursion(set);
	};
}