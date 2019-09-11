#include <functional>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch2/catch.hpp"

double MultiplyThreeNumbers(double one, double two, double three)
{
	return one * two * three;
}

std::function<double(double)> MultiplyThreeNumbers(double one, double two)
{
	return [one = one, two = two](double three)
	{
		return MultiplyThreeNumbers(one, two, three);
	};
}

std::function<std::function<double(double)>(double)> MultiplyThreeNumbers(double one)
{
	return [one = one](double two)
		{
			return MultiplyThreeNumbers(one, two);
		};
}


TEST_CASE("Currying performance testing")
{
	REQUIRE(24 == MultiplyThreeNumbers(2, 3, 4));
	REQUIRE(24 == MultiplyThreeNumbers(2, 3)(4));
	REQUIRE(24 == MultiplyThreeNumbers(2)(3)(4));

	BENCHMARK("Call three arg")
	{	
		for(double i = 2; i < 10; ++i)
		{
			MultiplyThreeNumbers(i, i+1, i+2);
		}
	};

	BENCHMARK("Call two arg")
	{	
		for(double i = 2; i < 10; ++i)
		{
			MultiplyThreeNumbers(i, i+1)(i+2);
		}
	};

	BENCHMARK("Call one arg")
	{	
		for(double i = 2; i < 10; ++i)
		{
			MultiplyThreeNumbers(i)(i+1)(i+2);
		}
	};
}