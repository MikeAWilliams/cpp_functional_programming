#include <functional>
#include <string>

#include "catch2/catch.hpp"

double AddFive(double in)
{
	return in + 5;
}

std::string AppendFive(const std::string& in)
{
	return in + "5";
}

template <typename Function>
auto PointerLifterFunction(Function f)
{
	return [f](auto* item)
	{
		if(nullptr != item)
		{
			return f(*item);
		}
	};
}

TEST_CASE("TestPointerLifterFunction")
{
	double value {10};
	REQUIRE(15 == PointerLifterFunction(AddFive)(&value));

	std::string stringValue{"1"};
	REQUIRE("15" == PointerLifterFunction(AppendFive)(&stringValue));
}

template <typename Function>
auto PointerLifterFunctionTwoArgument(Function f, auto* item)
{
	if(nullptr != item)
	{
		return f(*item);
	}
}

TEST_CASE("TestPointerLifterFunctionTwoArgument")
{
	double value {10};
	REQUIRE(15 == PointerLifterFunctionTwoArgument(AddFive,&value));

	std::string stringValue{"1"};
	REQUIRE("15" == PointerLifterFunctionTwoArgument(AppendFive, &stringValue));
}

class PointerLiftObject
{
public:
	template<typename Function>
	auto operator()(Function f, auto* item)
	{
		if(nullptr != item)
		{
			return f(*item);
		}
	} 
};

TEST_CASE("TestPointerLiftObject")
{
	double value {10};
	PointerLiftObject lifter;
	REQUIRE(15 == lifter(AddFive, &value));

	std::string stringValue{"1"};
	REQUIRE("15" == lifter(AppendFive, &stringValue));
}