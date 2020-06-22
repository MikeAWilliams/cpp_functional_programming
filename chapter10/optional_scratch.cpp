#include "catch2/catch.hpp"

#include <optional>

//Functional Programming in C++ by Ivan Cukic
// listing 10.1
template <typename T1, typename F>
auto transform(const std::optional<T1>& opt, F f) -> decltype(std::make_optional(f(opt.value())))
{
   if(opt)
   {
      return std::make_optional(f(opt.value()));
   }
   return {};
}

template <typename T1, typename F>
auto mbind(const std::optional<T1>& opt, F f) -> decltype(f(opt.value()))
{
   if(opt)
   {
      return f(opt.value());
   }
   return {};
}

double Add3(double value)
{
   return value + 3;
}

TEST_CASE("test transrom", "[optional_scratch]")
{
   auto resultWithEmpty = transform(std::optional<double>{}, Add3);
   REQUIRE_FALSE(resultWithEmpty);

   std::optional<double> optional2 { 2.0 };
   auto resultWithTwo = transform(optional2, Add3);
   REQUIRE(resultWithTwo);
   REQUIRE(resultWithTwo.value() == 5.0);
}

bool IsEven(int value)
{
   return value % 2 == 0;
}

TEST_CASE("IsEven", "[optional_scratch]")
{
   REQUIRE(IsEven(4));
   REQUIRE(IsEven(0));
   REQUIRE_FALSE(IsEven(3));
}

std::optional<int> Half(int value)
{
   if(IsEven(value))
   {
      return value / 2;
   }
   return {};
}

TEST_CASE("half", "[optional_scratch]")
{
  auto fourResult {Half(4)};
  REQUIRE(fourResult);
  REQUIRE(fourResult.value() == 2);

  auto threeResult {Half(3)};
  REQUIRE_FALSE(threeResult);
}

TEST_CASE("test mbind", "[optional_scratch]")
{
   auto fourResult {mbind(std::optional<int>{4}, Half)};
   REQUIRE(fourResult);
   REQUIRE(fourResult.value() == 2);

   auto threeResult {mbind(std::optional<int>{3}, Half)};
   REQUIRE_FALSE(threeResult);
}