#include <fstream>
#include <string>
#include <vector>

#include "range/v3/all.hpp"

#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"

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