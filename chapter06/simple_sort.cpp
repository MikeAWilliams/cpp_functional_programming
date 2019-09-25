#include "catch2/catch.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <random>
#include <forward_list>

template <class ForwardIt>
 void OutputContainer(ForwardIt first, ForwardIt last)
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

template <class ForwardIt>
 void simple_sort(ForwardIt first, ForwardIt last)
 {
    if(first == last) 
    {
        return;
    }
    auto distance {std::distance(first, last)};
    if(1 >= distance)
    {
        return;
    }

    auto pivotValue = *std::next(first, distance/2);

    ForwardIt middle1 = std::partition(first, last, [pivotValue](const auto& item)
        { 
            return item < pivotValue; 
        });
    ForwardIt middle2 = std::partition(middle1, last, [pivotValue](const auto& item)
        { 
            return pivotValue >= item; 
        });
    simple_sort(first, middle1);
    simple_sort(middle2, last);
 }

 template <class Container>
 void CompareTwoContainers(const Container& expected, const Container& result)
 {
    REQUIRE(expected.size() == result.size());

    auto expectedIter {expected.cbegin()};
    for(const auto & item : result)
    {
        REQUIRE(*expectedIter == item);
        ++expectedIter;
    }
 }

TEST_CASE("test simple sort happy path")
{
    std::vector<int> input {0, 9, 1, 8, 2, 7, 3, 6, 4, 5};

    std::vector<int> expected(10);
    std::iota(expected.begin(), expected.end(), 0);
    
    simple_sort(input.begin(), input.end());
    CompareTwoContainers(expected, input);
}