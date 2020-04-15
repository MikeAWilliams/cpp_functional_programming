#include <exception>
#include <functional>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "catch2/catch.hpp"

// write a revers polish calculator as described in Learn You A Haskell For Great Good
// http://learnyouahaskell.com/functionally-solving-problems#reverse-polish-notation-calculator

std::vector<std::string> Words(std::string words)
{
	std::istringstream wordStream{words};
	return std::vector<std::string>(std::istream_iterator<std::string>(wordStream), std::istream_iterator<std::string>());
}

static const std::unordered_map<std::string, std::function<int(int, int)>> SUPPORTED_OPERATIONS 
{
	{"+",std::plus<int>{}},
	{"-",std::minus<int>{}},
	{"*",std::multiplies<int>{}},
	{"/",std::divides<int>{}}
};

bool IsOperator(const std::string& word)
{
	return SUPPORTED_OPERATIONS.find(word) != SUPPORTED_OPERATIONS.end();
}

int ProcessOperator(const int first, const int second, std::string op)
{
	auto functionIter {SUPPORTED_OPERATIONS.find(op)};
	if(SUPPORTED_OPERATIONS.end() == functionIter)
	{
		throw std::logic_error("Invalid operator provided");
	}
	return functionIter->second(second, first);
}

std::stack<std::string> ProcessOperator(std::stack<std::string> stack, std::string op)
{
	int first {std::stoi(stack.top())};
	stack.pop();
	int second {std::stoi(stack.top())};
	stack.pop();
	int result {ProcessOperator(first, second, std::move(op))};

	stack.push(std::to_string(result));
	return stack;
}

std::stack<std::string> RPNBinaryOperator(std::stack<std::string> stack, std::string element)
{
	if(IsOperator(element))
	{
		stack = ProcessOperator(std::move(stack), std::move(element));
	}
	else
	{
		stack.push(element);
	}
	return stack;
}

int CalculateRPN(std::string rpnExpression)
{
	const auto words {Words(std::move(rpnExpression))};
	auto accResult {std::accumulate(words.cbegin(), words.cend(), std::stack<std::string>{}, RPNBinaryOperator)};
	if(1 != accResult.size())
	{
		throw std::logic_error{"the fold didn't work"};
	}
	return std::stoi(accResult.top());
}

TEST_CASE("all operators return true", "[IsOperator][RPN]")
{
	const std::vector<std::string> requiredOperators {"+", "-", "*", "/"};
	for(const auto & op : requiredOperators)
	{
		REQUIRE(IsOperator(op));
	}
}

TEST_CASE("test words", "[RPN][words]")
{
	const std::vector<std::string> expectedResult {"1", "1", "+"};
	auto words {Words("1 1 +")};

	REQUIRE(expectedResult == words);
}

TEST_CASE("new element is a number starts empty", "[RPN][BinaryOperator]")
{
	std::stack<std::string> expectedResult;
	expectedResult.push("3");

	auto result {RPNBinaryOperator({}, "3")};

	REQUIRE(expectedResult == result);
}

TEST_CASE("new element is a number starts not empty", "[RPN][BinaryOperator]")
{
	std::stack<std::string> expectedResult;
	expectedResult.push("4");
	std::stack<std::string> initialStack {expectedResult};
	expectedResult.push("3");

	auto result {RPNBinaryOperator(std::move(initialStack), "3")};

	REQUIRE(expectedResult == result);
}

TEST_CASE("new element is +", "[RPN][BinaryOperator]")
{
	std::stack<std::string> expectedResult;
	expectedResult.push("4");

	std::stack<std::string> initialStack;
	initialStack.push("2");
	initialStack.push("2");

	auto result {RPNBinaryOperator(std::move(initialStack), "+")};

	REQUIRE(expectedResult == result);
}

TEST_CASE("new element is -", "[RPN][BinaryOperator]")
{
	std::stack<std::string> expectedResult;
	expectedResult.push("2");

	std::stack<std::string> initialStack;
	initialStack.push("12");
	initialStack.push("10");

	auto result {RPNBinaryOperator(std::move(initialStack), "-")};

	REQUIRE(expectedResult == result);
}

TEST_CASE("new element is *", "[RPN][BinaryOperator]")
{
	std::stack<std::string> expectedResult;
	expectedResult.push("120");

	std::stack<std::string> initialStack;
	initialStack.push("12");
	initialStack.push("10");

	auto result {RPNBinaryOperator(std::move(initialStack), "*")};

	REQUIRE(expectedResult == result);
}

TEST_CASE("new element is /", "[RPN][BinaryOperator]")
{
	std::stack<std::string> expectedResult;
	expectedResult.push("10");

	std::stack<std::string> initialStack;
	initialStack.push("120");
	initialStack.push("12");

	auto result {RPNBinaryOperator(std::move(initialStack), "/")};

	REQUIRE(expectedResult == result);
}

TEST_CASE("test two numbers add", "[RPN]")
{
	REQUIRE(2 == CalculateRPN("1 1 +"));
}

TEST_CASE("test two numbers subtract", "[RPN]")
{
	REQUIRE(3 == CalculateRPN("4 1 -"));
}

TEST_CASE("test two numbers multiply", "[RPN]")
{
	REQUIRE(16 == CalculateRPN("4 4 *"));
}

TEST_CASE("test two numbers devide", "[RPN]")
{
	REQUIRE(2 == CalculateRPN("4 2 /"));
}

TEST_CASE("complex", "[RPN]")
{
	REQUIRE(-4 == CalculateRPN("10 4 3 + 2 * -"));
}

TEST_CASE("complex with devide", "[RPN]")
{
	REQUIRE(2 == CalculateRPN("10 4 3 + 2 * - -2 /"));
}