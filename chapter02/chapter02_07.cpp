#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include <iostream>

#include "range/v3/all.hpp"

#include "catch2/catch.hpp"

struct Person
{
	std::string Name;
	bool IsFemale;
};

bool IsFremale(const Person& person)
{
	return person.IsFemale;
}

bool IsNotFemale(const Person& person)
{
	return !person.IsFemale;
}

std::string Name(const Person& person)
{
	return person.Name;
}

std::vector<std::string> GetNamesOfFemales(std::vector<Person> people)
{
	people.erase(std::remove_if(people.begin(), people.end(), IsNotFemale), people.end());

	std::vector<std::string> result(people.size());
	std::transform(people.begin(), people.end(), result.begin(), Name);
	return result;
}

template<typename t>
void RequireVectorsMatchUnordered(std::vector<t>& first, std::vector<t>& second)
{
	REQUIRE(first.size() == second.size());
	std::sort(first.begin(), first.end());
	std::sort(second.begin(), second.end());
	REQUIRE(first == second);
}

TEST_CASE("GetNamesOfFemalesMixed")
{
	std::vector<Person> input {{"Bob", false}, {"Susan", true}, {"Joe", false}, {"Stephanie", true}};
	std::vector<std::string> expectedResult {"Stephanie", "Susan"};

	auto result {GetNamesOfFemales(input)};
	RequireVectorsMatchUnordered(expectedResult, result);
}

TEST_CASE("GetNamesOfFemalesAllMale")
{
	std::vector<Person> input {{"Bob", false}, {"Susan", false}, {"Joe", false}, {"Stephanie", false}};
	std::vector<std::string> expectedResult {};

	auto result {GetNamesOfFemales(input)};
	RequireVectorsMatchUnordered(expectedResult, result);
}

TEST_CASE("GetNamesOfFemalesAllFemale")
{
	std::vector<Person> input {{"Bob", true}, {"Susan", true}, {"Joe", true}, {"Stephanie", true}};
	std::vector<std::string> expectedResult {"Bob", "Joe", "Susan", "Stephanie"};

	auto result {GetNamesOfFemales(input)};
	RequireVectorsMatchUnordered(expectedResult, result);
}