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


unsigned int Factorial(unsigned int number) {
	return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("range example 1", "[ranges]")
{
	std::vector<int> vi{ 1,2,3,4,5,6,7,8,9,10 };
	using namespace ranges;
	auto rng = vi | views::remove_if([](int i) {return i % 2 == 1; })
		| views::transform([](int i) {return std::to_string(i); });

	std::cout << rng << std::endl;
}

int count_lines(const std::string& filename)
{
	std::ifstream in(filename);
	auto newlines {std::count(std::istreambuf_iterator<char>(in),
		std::istreambuf_iterator<char>(), '\n')};
	return newlines + 1;
}

std::vector<int> count_lines_in_files(const std::vector<std::string>& files)
{
	std::vector<int> results(files.size());
	std::transform(files.cbegin(), files.cend(), results.begin(), count_lines);
	return results;
}

TEST_CASE("test countliens")
{
	auto lines = count_lines("build.sh");
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

// come back and try https://ericniebler.github.io/range-v3/index.html#example-hello

auto is_six = [](int i) { return i == 6; };

TEST_CASE("any_of-all_of-none_of")
{
    std::vector<int> v{6, 2, 3, 4, 5, 6};
    std::cout << std::boolalpha;
    std::cout << "vector: " << ranges::views::all(v) << '\n';
 
    REQUIRE(ranges::any_of(v, is_six));
    REQUIRE_FALSE(ranges::all_of(v, is_six));
    REQUIRE_FALSE(ranges::none_of(v, is_six));
}