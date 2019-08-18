#define CATCH_CONFIG_MAIN 
#include <vector>
#include <iostream>
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

TEST_CASE("sort", "[ranges]")
{
	std::vector<int> vi{ 1,2,3,4,5,6,7,8,9,10 };
	using namespace ranges;
	auto rng = vi | views::remove_if([](int i) {return i % 2 == 1; })
		| views::transform([](int i) {return std::to_string(i); });

	std::cout << rng << " " << typeid(rng).name() << std::endl;
}