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