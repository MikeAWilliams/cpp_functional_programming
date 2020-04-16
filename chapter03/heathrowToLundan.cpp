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
	previousState.aPath.AddSection(PathSection{'A', newSection.costA});
	previousState.bPath.AddSection(PathSection{'B', newSection.costB});
	return previousState;
}

bool ComparePathCostPair(const PathCostPair& left, const PathCostPair& right)
{
	if(left.cost != right.cost)
	{
		return false;
	}

	if(left.path.size() != right.path.size())
	{
		return false;
	}

	auto leftIter {left.path.cbegin()};
	for(const auto& rightSection : right.path)
	{
		if(leftIter->cost != rightSection.cost)
		{
			return false;
		}
		if(leftIter->label != rightSection.label)
		{
			return false;
		}
		++leftIter;
	}
	return true;
}

TEST_CASE("Forward price is less for both", "[heathrowToLundan][testFoldingFunction]")
{
	const RoadSection inputSection {10, 11, 100};
	PathAlternatives initialAlternatives {PathCostPair{Path{}, 0}, PathCostPair{Path{}, 0}};
	PathAlternatives expectedAlternatives {initialAlternatives};

	expectedAlternatives.aPath.AddSection(PathSection{'A', 10});
	expectedAlternatives.bPath.AddSection(PathSection{'B', 11});

	auto result {SingleStepFoldingFuction(std::move(initialAlternatives), std::move(inputSection))};
	REQUIRE(ComparePathCostPair(expectedAlternatives.aPath, result.aPath));
	REQUIRE(ComparePathCostPair(expectedAlternatives.bPath, result.bPath));
}
