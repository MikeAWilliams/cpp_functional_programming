#include <exception>
#include <functional>
#include <iostream>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/catch.hpp"

int64_t FactorialLoop(int64_t n)
{
	if(n <= 0)
	{
		throw std::range_error("n required to be > 0");
	}
	
	int64_t result{n};
	for(n -= 1; n > 1; --n)
	{
		result *= n;
	}
	
	return result;
}

int64_t FactorialTailRecursion(int64_t n)
{
	if(n <= 0)
	{
		throw std::range_error("n required to be > 0");
	}
	if(1 == n)
	{
		return 1;
	}

	return n * FactorialTailRecursion(n - 1);
}

int64_t FactorialNonTailRecursion(int64_t n)
{
	if(n <= 0)
	{
		throw std::range_error("n required to be > 0");
	}
	if(1 == n)
	{
		return 1;
	}

	const auto volatile recursiveResult {FactorialNonTailRecursion(n - 1)};
	return n * recursiveResult;
}

static void RunTestFactorial(std::function<int64_t(int64_t)> toTest)
{
	REQUIRE_THROWS(toTest(-5));
	REQUIRE_THROWS(toTest(0));
	REQUIRE(1 == toTest(1));
	REQUIRE(2 == toTest(2));
	REQUIRE(6 == toTest(3));
	REQUIRE(24 == toTest(4));
}

TEST_CASE("FactorialLoop")
{
	RunTestFactorial(FactorialLoop);
}

TEST_CASE("FactorialTailRecursion")
{
	RunTestFactorial(FactorialTailRecursion);
}

TEST_CASE("FactorialNonTailRecursion")
{
	RunTestFactorial(FactorialNonTailRecursion);
}

TEST_CASE("Factorial performance testing")
{
	const int64_t input{64};
	int64_t resultLoop;
	int64_t resultTail;
	int64_t resultNonTail;
	BENCHMARK("loop")
	{	
		resultLoop = FactorialLoop(input);
	};

	BENCHMARK("tail recursion")
	{	
		resultTail = FactorialTailRecursion(input);
	};

	BENCHMARK("no tail recursion")
	{
		resultNonTail = FactorialNonTailRecursion(input);
	};

	REQUIRE(resultTail == resultLoop);
	REQUIRE(resultTail == resultNonTail);
}