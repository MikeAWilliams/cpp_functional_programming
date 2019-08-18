#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "range/v3/all.hpp"

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

int LinesInString_Accumulate(const std::string input)
{
	return std::accumulate(input.cbegin(), input.cend(), 0, CountIfNewline);
}

TEST_CASE("CountIfNewline")
{
	REQUIRE(5 == CountIfNewline(4, '\n'));
	REQUIRE(1 == CountIfNewline(0, '\n'));
	REQUIRE(-2 == CountIfNewline(-3, '\n'));

	REQUIRE(0 == CountIfNewline(0, 'n'));
	REQUIRE(7 == CountIfNewline(7, 'w'));
}

TEST_CASE("NewLineInString Accumulate")
{
	std::string input {"The\nanswer\nis\nthree"};

	auto result {LinesInString_Accumulate(input)};
	REQUIRE(3 == result);

	input = "\nthe\nanswoer\nis\nfour";
	result = LinesInString_Accumulate(input);
	REQUIRE(4 == result);
}