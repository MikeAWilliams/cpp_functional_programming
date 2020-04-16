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

// solve the Heathrow to Londan problem as proposed in Learn You a Haskell For Great Good
// http://learnyouahaskell.com/functionally-solving-problems#reverse-polish-notation-calculator

struct RoadSection
{
	int costA;
	int costB;
	int costC;
};

using RoadSystem = std::vector<RoadSection>;

const RoadSystem ExampleRoadSystem {{50, 10, 30}, {5, 90, 20}, {40, 2, 25}, {10, 8, 0}};

struct PathSection
{
	char label;
	int cost;

	bool operator==(const PathSection& other) const
	{
		return label == other.label && cost == other.cost;
	}
};

using Path = std::vector<PathSection>;

struct PathCostPair
{
	Path path;
	int cost;

	PathCostPair(Path p, int c)
		: path {std::move(p)}
		, cost {c}
	{
	}

	PathCostPair(const PathCostPair& other)
		: path {other.path}
		, cost {other.cost}
	{
	}

	void AddSection(PathSection newSection)
	{
		cost += newSection.cost;
		path.push_back(newSection);
	}

	bool operator==(const PathCostPair& other) const
	{
		return cost == other.cost && path == other.path;
	}
};

struct PathAlternatives
{
	PathCostPair aPath;
	PathCostPair bPath;

	PathAlternatives(PathCostPair a, PathCostPair b)
		: aPath {std::move(a)}
		, bPath {std::move(b)}
	{
	}

	PathAlternatives(const PathAlternatives& other)
		: aPath {other.aPath}
		, bPath {other.bPath}
	{
	}
};

PathAlternatives SingleStepFoldingFuction(PathAlternatives previousState, RoadSection newSection)
{
	const int forwardToACost {previousState.aPath.cost + newSection.costA};
	const int crossToACost {previousState.bPath.cost + newSection.costB + newSection.costB};
	if(forwardToACost <= crossToACost)
	{
		previousState.aPath.AddSection(PathSection{'A', newSection.costA});
	}
	else
	{
		previousState.aPath.AddSection(PathSection{'B', newSection.costB});
		previousState.aPath.AddSection(PathSection{'C', newSection.costC});
	}
	
	previousState.bPath.AddSection(PathSection{'B', newSection.costB});
	return previousState;
}

TEST_CASE("Forward price is less for both inital empty", "[heathrowToLundan][testFoldingFunction]")
{
	const RoadSection inputSection {10, 11, 100};
	PathAlternatives initialAlternatives {PathCostPair{Path{}, 0}, PathCostPair{Path{}, 0}};
	PathAlternatives expectedAlternatives {initialAlternatives};

	expectedAlternatives.aPath.AddSection(PathSection{'A', 10});
	expectedAlternatives.bPath.AddSection(PathSection{'B', 11});

	auto result {SingleStepFoldingFuction(std::move(initialAlternatives), std::move(inputSection))};
	REQUIRE(expectedAlternatives.aPath == result.aPath);
	REQUIRE(expectedAlternatives.bPath == result.bPath);
}

TEST_CASE("Forward cost to a is high initial empty", "[heathrowToLundan][testFoldingFunction]")
{
	const RoadSection inputSection {100, 10, 11};
	PathAlternatives initialAlternatives {PathCostPair{Path{}, 0}, PathCostPair{Path{}, 0}};
	PathAlternatives expectedAlternatives {initialAlternatives};

	expectedAlternatives.aPath.AddSection(PathSection{'B', 10});
	expectedAlternatives.aPath.AddSection(PathSection{'C', 11});
	expectedAlternatives.bPath.AddSection(PathSection{'B', 10});

	auto result {SingleStepFoldingFuction(std::move(initialAlternatives), std::move(inputSection))};
	REQUIRE(expectedAlternatives.aPath == result.aPath);
	REQUIRE(expectedAlternatives.bPath == result.bPath);
}

TEST_CASE("Forward cost to b is high initial empty", "[heathrowToLundan][testFoldingFunction]")
{
	const RoadSection inputSection {10, 100, 11};
	PathAlternatives initialAlternatives {PathCostPair{Path{}, 0}, PathCostPair{Path{}, 0}};
	PathAlternatives expectedAlternatives {initialAlternatives};

	expectedAlternatives.aPath.AddSection(PathSection{'A', 10});
	expectedAlternatives.bPath.AddSection(PathSection{'A', 10});
	expectedAlternatives.bPath.AddSection(PathSection{'C', 11});

	auto result {SingleStepFoldingFuction(std::move(initialAlternatives), std::move(inputSection))};
	REQUIRE(expectedAlternatives.aPath == result.aPath);
	REQUIRE(expectedAlternatives.bPath == result.bPath);
}