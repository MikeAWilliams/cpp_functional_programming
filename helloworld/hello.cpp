#define CATCH_CONFIG_MAIN 
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/none_of.hpp>
#include "catch2/catch.hpp"
#include "range/v3/all.hpp"


// this is the first example on https://ericniebler.github.io/range-v3/ 

TEST_CASE("range example 1", "[ranges]")
{
	std::vector<int> vi{ 1,2,3,4,5,6,7,8,9,10 };
	using namespace ranges;
	auto rng = vi | views::remove_if([](int i) {return i % 2 == 1; })
		| views::transform([](int i) {return std::to_string(i); });

	std::cout << rng << std::endl;
}

// random examples fromhttps://ericniebler.github.io/range-v3/index.html#example-hello

auto is_six = [](int i) { return i == 6; };

TEST_CASE("any_of-all_of-none_of")
{
    std::vector<int> v{6, 2, 3, 4, 5, 6};
 
    REQUIRE(ranges::any_of(v, is_six));
    REQUIRE_FALSE(ranges::all_of(v, is_six));
    REQUIRE_FALSE(ranges::none_of(v, is_six));
}

TEST_CASE("count")
{
	std::vector<int> data{6,2,3,4,5,6};
	auto count = ranges::count(data, 6);
	REQUIRE(2 == count);

	auto countIfResult = ranges::count_if(data, is_six);
	REQUIRE(2 == countIfResult);
}

TEST_CASE("for each")
{
	int sum{0};
	auto badSum = [&sum](int item) {sum += item;};
    std::vector<int> data{6, 2, 3, 4, 5, 6};
	ranges::for_each(data, badSum);

	REQUIRE(26 == sum);
}

TEST_CASE("Composability")
{
	auto sum = ranges::accumulate(ranges::views::ints(1, 11)
		| ranges::views::transform([](int i)
			{
				return i*i;
			}), 0);
	REQUIRE(385 == sum);

	auto sumSimple = ranges::accumulate(ranges::views::ints(1,11), 0);
	REQUIRE(55 == sumSimple);

	std::vector<int> data{ 1,2,3,4,5,6,7,8,9,10 };
	auto specifyResult = ranges::accumulate(data | ranges::views::remove_if([](int i) {return i % 2 == 1; }), 0);

	REQUIRE(30 == specifyResult);
}

// I wanted to understand this example from chapter 1. I will start to organize by chapter after I get this to work

std::ifstream open_file(const std::string& file)
{
	return std::ifstream(file);
}

int count_lines(std::ifstream file)
{
	auto newlines {std::count(std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>(), '\n')};
	return newlines + 1;
}

std::vector<int> count_lines_in_files(const std::vector<std::string>& files)
{
	return ranges::to_vector(files 
		| ranges::views::transform(open_file)
		| ranges::views::transform(count_lines));
}

TEST_CASE("test countliens")
{
	auto lines = count_lines(open_file("build.sh"));
	REQUIRE(4 ==  lines);
}

TEST_CASE("test count_liens_in_files")
{
	std::vector<std::string> files {"build.sh", "CMakeLists.txt"};
	auto result = count_lines_in_files(files);
	REQUIRE(2 == result.size());
	REQUIRE(4 == result[0]);
	REQUIRE(7 == result[1]);
}