#include "catch2/catch.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "range/v3/all.hpp"

template <typename Range>
std::vector<std::string> get_top_ten(const Range& movies)
{
    auto items {ranges::view::zip(movies, ranges::view::ints(1)) 
        | ranges::view::transform([](const auto & pair)
        {
            return std::to_string(pair.second) + " " + pair.first;
        })
        | ranges::view::take(10)
        | ranges::to<std::vector>};

    return items;
}

TEST_CASE("FAIL")
{
    std::vector<std::string> movies {"terminator", "the last unicorn", "movies3", "movie4", "movie5", "movie6", "movie7", "movie8", "movie9", "movie10", "movie11"};
    auto result {get_top_ten(movies)};
    REQUIRE(10 == result.size());
}

std::string string_to_lower(const std::string&s)
{
    return s | ranges::view::transform(tolower);
}

std::string string_only_alnum(const std::string& s)
{
    return s | ranges::view::filter(isalnum);
}

std::vector<std::string> GetFilteredWordsFromCIN()
{
    std::cout << "Enter some words, end with ctrl-d" << std::endl;
    std::vector<std::string> result {
        ranges::istream_range<std::string>(std::cin)
        | ranges::view::transform(string_to_lower)
        | ranges::view::transform(string_only_alnum)
        | ranges::view::remove_if(&std::string::empty)
    };
    return result;
}

TEST_CASE("GetFilteredWordsFromCIN")
{
//    auto result {GetFilteredWordsFromCIN()};
    //std::cout << std::endl << "The word results are " << std::endl;
    //for(const auto & word : result)
    //{
        //std::cout << word << std::endl;
    //}
    //REQUIRE(false);
}

std::vector<std::pair<long int, std::string>> TakeNMostCommonWords(const std::vector<std::string>& words)
{
    const auto results {
        words | ranges::view::group_by(std::equal_to<>())
              | ranges::view::transform([](const auto& group)
              {
                  const auto begin {std::begin(group)};
                  const auto end {std::end(group)};
                  const auto count {ranges::distance(begin, end)};
                  const auto word {*begin};

                  return std::make_pair(count, word);
              })
              | ranges::to_vector | ranges::action::sort };
    return results;
}

TEST_CASE("TakeNMostCommonWords")
{
    auto words {GetFilteredWordsFromCIN()};
    auto result {TakeNMostCommonWords(words)};

    std::cout << std::endl << "reversed result is" << std::endl;
    for(const auto value : result | ranges::view::reverse)
    {
        std::cout << value.first << " " << value.second << std::endl;
    }
}