#include "catch2/catch.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <class Iterator>
 void OutputContainer(Iterator first, Iterator last)
 {
    if(first == last)
    {
        return;
    }
    for(; first != last; ++first)
    {
        std::cout << *first << std::endl;
    }
 }

template <class Iterator>
 void lazy_sort(Iterator first, Iterator positionToSortTo, Iterator last)
 {
    std::nth_element(first, positionToSortTo, last);
    std::sort(first, positionToSortTo);
 }

TEST_CASE("test lazy sort happy path")
{
    constexpr size_t const LAST_SORTED_INDEX {3};
    std::vector<int> input {9, 0, 8, 1, 7, 2, 6, 3, 4, 5};

    lazy_sort(input.begin(), std::next(input.begin(), LAST_SORTED_INDEX), input.end());

    for(size_t i = 0; i < LAST_SORTED_INDEX; ++i)
    {
        REQUIRE(i == input[i]);
    }
}