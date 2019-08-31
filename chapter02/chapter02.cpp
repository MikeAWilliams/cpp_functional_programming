#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include <iostream>

#include "range/v3/all.hpp"

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"

int CountIfNewline(int previousCount, char currentCharacter)
{
	if('\n' != currentCharacter)
	{
		return previousCount;
	}
	return previousCount + 1;
}

TEST_CASE("CountIfNewline")
{
	REQUIRE(5 == CountIfNewline(4, '\n'));
	REQUIRE(1 == CountIfNewline(0, '\n'));
	REQUIRE(-2 == CountIfNewline(-3, '\n'));

	REQUIRE(0 == CountIfNewline(0, 'n'));
	REQUIRE(7 == CountIfNewline(7, 'w'));
}

int LinesInString_Accumulate(const std::string input)
{
	return std::accumulate(input.cbegin(), input.cend(), 0, CountIfNewline);
}

void TestNewlineCountinfFunction(std::function<int(const std::string)> f)
{
	std::string input {"The\nanswer\nis\nthree"};

	auto result {f(input)};
	REQUIRE(3 == result);

	input = "\nthe\nanswoer\nis\nfour";
	result = f(input);
	REQUIRE(4 == result);
}

TEST_CASE("NewLineInString Accumulate")
{
	TestNewlineCountinfFunction(LinesInString_Accumulate);
}

int OneIfCharIsNewline(const char c)
{
	if('\n' == c)
	{
		return 1;
	}
	return 0;
}

TEST_CASE("OneIfCharIsNewline")
{
	REQUIRE(0 == OneIfCharIsNewline('n'));
	REQUIRE(0 == OneIfCharIsNewline('a'));
	REQUIRE(1 == OneIfCharIsNewline('\n'));
}

int LinesInString_RangeAccumulate(const std::string input)
{
	//return ranges::accumulate(input ! ranges::views::transform(OneIfCharIsNewline), 0);
	// the above does not compile, but the below, with the intermediate range result does...
	auto transformed {input | ranges::views::transform(OneIfCharIsNewline)};
	return ranges::accumulate(transformed, 0);
}

TEST_CASE("NewLineInString RangeAccumulate")
{
	TestNewlineCountinfFunction(LinesInString_RangeAccumulate);
}