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
 void lazy_sort(Iterator first, Iterator last, size_t sortSize)
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

    //std::cout << "\nInput value\n";
    //OutputContainer(first, last);

    auto pivotValue = *std::next(first, distance/2);

    //std::cout << "\npivot value " << pivotValue;

    Iterator middle1 = std::partition(first, last, [pivotValue](const auto& item)
        { 
            return item < pivotValue; 
        });

    //std::cout << "\nAfter pivot 1\n";
    //OutputContainer(first, last);

    Iterator middle2 = std::partition(middle1, last, [pivotValue](const auto& item)
        { 
            return pivotValue >= item; 
        });

    //std::cout << "\nAfter pivot 2\n";
    //OutputContainer(first, last);

    lazy_sort(first, middle1, sortSize);

    auto firstHalfDistance {std::distance(first, middle1)};
    if(firstHalfDistance < sortSize)
    {
        //std::cout << "running second half\n";
        lazy_sort(middle2, last, sortSize);
    }
 }

TEST_CASE("test lazy sort happy path")
{
    std::vector<int> input {0, 4, 3, 2, 1, 5, 9, 8, 7, 6};

    lazy_sort(input.begin(), input.end(), 5);

    for(size_t i = 0; i < 5; ++i)
    {
        REQUIRE(i == input[i]);
    }

    OutputContainer(input.begin(), input.end());
}