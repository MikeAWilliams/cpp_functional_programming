#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include <iostream>

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
std::vector<resultType> FilterTransform(
	iteratorType data_begin,
	iteratorType data_end,
	std::function<bool(const inputType&)> filter,
	std::function<resultType(const inputType&)> transform)
{
	std::vector<resultType> result;
	return result;
}

static std::vector<std::string> GetNamesOfFemales(const std::vector<Person>& people)
{
	return FilterTransform<std::string, Person, std::vector<Person>::const_iterator>(people.cbegin(), people.cend(), 
	    [](const Person& p)
		{
			return IsFemale(p);
		},
		[](const Person& p)
		{
			return Name(p); 
		});
}

template<typename t>
static void RequireVectorsMatchUnordered(std::vector<t>& first, std::vector<t>& second)
{
	REQUIRE(first.size() == second.size());
	std::sort(first.begin(), first.end());
	std::sort(second.begin(), second.end());
	REQUIRE(first == second);
}

TEST_CASE("GetNamesOfFemalesMixed_14")
{
	std::vector<Person> input {{"Bob", false}, {"Susan", true}, {"Joe", false}, {"Stephanie", true}};
	std::vector<std::string> expectedResult {"Stephanie", "Susan"};

	auto result {GetNamesOfFemales(input)};
	RequireVectorsMatchUnordered(expectedResult, result);
}

TEST_CASE("GetNamesOfFemalesAllMale_14")
{
	std::vector<Person> input {{"Bob", false}, {"Susan", false}, {"Joe", false}, {"Stephanie", false}};
	std::vector<std::string> expectedResult {};

	auto result {GetNamesOfFemales(input)};
	RequireVectorsMatchUnordered(expectedResult, result);
}

TEST_CASE("GetNamesOfFemalesAllFemale_14")
{
	std::vector<Person> input {{"Bob", true}, {"Susan", true}, {"Joe", true}, {"Stephanie", true}};
	std::vector<std::string> expectedResult {"Bob", "Joe", "Susan", "Stephanie"};

	auto result {GetNamesOfFemales(input)};
	RequireVectorsMatchUnordered(expectedResult, result);
}