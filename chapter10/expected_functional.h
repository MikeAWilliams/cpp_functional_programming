#include "tl/expected.hpp"

template <typename T, typename E, typename F>
tl::expected<T,E> transform(const tl::expected<T,E>& exp, F f)
{
   if(exp)
   {
      return f(*exp);
   }
   return tl::make_unexpected(exp.error());
}

//auto transform(const std::optional<T1>& opt, F f) -> decltype(std::make_optional(f(opt.value())))
//{
   //if(opt)
   //{
      //return std::make_optional(f(opt.value()));
   //}
   //return {};
//}

//template <typename T1, typename F>
//auto mbind(const std::optional<T1>& opt, F f) -> decltype(f(opt.value()))
//{
   //if(opt)
   //{
      //return f(opt.value());
   //}
   //return {};
//}