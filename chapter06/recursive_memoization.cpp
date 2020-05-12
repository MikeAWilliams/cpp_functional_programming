#include "catch2/catch.hpp"
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>

class null_param{};

template <class Sig, class F>
class memoize_helper;

template<class Result, class... Args, class F>
class memoize_helper<Result(Args...), F>
{
private:
    using function_type = F;
    using args_tuple_type = std::tuple<std::decay_t<Args>...>;

    function_type f;
    mutable std::map<args_tuple_type, Result> m_cache;
    mutable std::recursive_mutex m_cache_mutex;

public:
    template <typename Function>
    memoize_helper(Function&& f, null_param)
    : f(f){}

    memoize_helper(const memoize_helper& other)
    : f(other.f) { }

    template<class... InnerArgs>
    Result operator()(InnerArgs&&... args) const
    {
        std::unique_lock<std::recursive_mutex> lock{m_cache_mutex};

        const auto args_tuple {std::make_tuple(args...)};
        const auto cachedIter {m_cache.find(args_tuple)};

        if(cachedIter != m_cache.end())
        {
            std::cout << "Hit cache\n";
            return cachedIter->second;
        }
        std::cout << "Missed cache\n";
        auto&& result {f(*this, std::forward<InnerArgs>(args)...)};
        m_cache[args_tuple] = result;
        return result;
    }
};

template <class Sig, class F>
memoize_helper<Sig, std::decay_t<F>> make_memoized_r(F&& f)
{
    return {std::forward<F>(f), null_param()};
}

TEST_CASE("Test mem-fib")
{
    auto fibmemo = make_memoized_r<unsigned int(unsigned int)>(
        [](auto& fib, unsigned int n){
            std::cout << "Calculating " << n << "\n";
            return n == 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);
        });
    std::cout << "First Call 6\n\n";
    REQUIRE(8 == fibmemo(6));
    std::cout << "Second Call 6\n\n";
    REQUIRE(8 == fibmemo(6));

    std::cout << "First Call 8\n\n";
    REQUIRE(21 == fibmemo(8));
}