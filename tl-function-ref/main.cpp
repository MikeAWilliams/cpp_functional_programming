#define CATCH_CONFIG_MAIN 
#include "catch2/catch.hpp"
#include <tl/function_ref.hpp>

bool f_called = false;
void f(){f_called=true;}

TEST_CASE("first")
{
   tl::function_ref<void(void)> fr = f;
   fr();
   REQUIRE(f_called);
}