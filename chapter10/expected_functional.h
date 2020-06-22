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

template <typename T, typename E, typename F>
tl::expected<T,E> mbind(const tl::expected<T,E>& exp, F f)
{
   if(exp)
   {
      return f(*exp);
   }
   return tl::make_unexpected(exp.error());
}