#include "catch2/catch.hpp"
#include "immer/array.hpp"

#include <vector>

template<typename Container>
void CheckUndoState(std::vector<Container> toCheck)
{
    for(size_t toCheckIndex{1}; toCheckIndex < toCheck.size(); ++toCheckIndex)
    {
        for(size_t itemIndex {0}; itemIndex < toCheckIndex - 1; ++itemIndex)
        {
            INFO("toCheckIndex:" + std::to_string(toCheckIndex) + " itemIndex:" + std::to_string(itemIndex));
            REQUIRE(toCheck[toCheckIndex][itemIndex] == itemIndex);
        }
    }
}

TEST_CASE("check check function", "[immer]")
{
    std::vector<std::vector<int>> goodVector {
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 0},
        {0, 9, 9, 9, 9, 9, 9, 9, 9, 0},
        {0, 1, 9, 9, 9, 9, 9, 9, 9, 0},
        {0, 1, 2, 9, 9, 9, 9, 9, 9, 0},
        {0, 1, 2, 3, 9, 9, 9, 9, 9, 0},
        {0, 1, 2, 3, 4, 9, 9, 9, 9, 0},
        {0, 1, 2, 3, 4, 5, 9, 9, 9, 0},
        {0, 1, 2, 3, 4, 5, 6, 9, 9, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 9, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 0},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    };
    CheckUndoState(std::move(goodVector));
}

std::vector<std::vector<int>> MakeUndoState(std::vector<int> initialState)
{
    std::vector<std::vector<int>> result;
    result.reserve(initialState.size());

    for(size_t index {0}; index < initialState.size(); ++index)
    {
        result.push_back(initialState);
        initialState[index] = index;
    }

    return result;
}

TEST_CASE("check MakeUndoState vector", "[immer]")
{
    std::vector<int> init(500, -100);
    auto result = MakeUndoState(init);
    CheckUndoState(std::move(result));
}

std::vector<immer::array<int>> MakeUndoState(immer::array<int> initialState)
{
    std::vector<immer::array<int>> result;
    result.reserve(initialState.size());

    for(size_t index {0}; index < initialState.size(); ++index)
    {
        result.push_back(initialState);
        initialState = std::move(initialState).set(index, index);
    }

    return result;
}

TEST_CASE("check MakeUndoState immerArray", "[immer]")
{
    immer::array<int> init(500, -100);
    auto result = MakeUndoState(init);
    CheckUndoState(std::move(result));
}