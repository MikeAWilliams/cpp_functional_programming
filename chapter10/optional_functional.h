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