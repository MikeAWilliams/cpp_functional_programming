
#include "catch2/catch.hpp"

#include "logger.h"

TEST_CASE("test constructor no log", "[logger]")
{
   const Logger<int> testObject{42};
   REQUIRE(42 == testObject.Value());
   REQUIRE(0 == testObject.Log().size());
}

TEST_CASE("test constructor with log", "[logger]")
{
   constexpr auto message {"the ansswer"};
   const Logger<int> testObject{42, message};
   REQUIRE(42 == testObject.Value());
   auto log {testObject.Log()};
   REQUIRE(1 == log.size());
   REQUIRE(message == log[0]);
}

TEST_CASE("test constructor with vector log", "[logger]")
{
   std::vector<std::string> oldLog;
   oldLog.emplace_back("log 1");
   oldLog.emplace_back("log 2");

   const Logger<int> testObject{42, oldLog};
   REQUIRE(42 == testObject.Value());
   auto log {testObject.Log()};
   REQUIRE(oldLog.size() == log.size());

   auto oldLogIter {oldLog.begin()};
   for(const auto& logItem : log)
   {
      REQUIRE(*oldLogIter == logItem);
      ++oldLogIter;
   }
}

TEST_CASE("test transform", "[logger]")
{
   constexpr auto message {"the ansswer"};
   const Logger<int> testObject{42, message};

   auto result{transform(testObject, 
      [](int value)
      { 
         return value + 3;
      })};

   REQUIRE(45 == result.Value());
   auto log{result.Log()};
   REQUIRE(1 == log.size());
   REQUIRE(message == log[0]);
}

TEST_CASE("test mbind", "[logger]")
{
   constexpr auto message {"the ansswer"};
   constexpr auto add_message {"added 3"};
   const Logger<int> testObject{42, message};

   auto result{mbind(testObject, 
      [add_message](int value)
      { 
         return Logger<int>{value + 3, add_message};
      })};

   REQUIRE(45 == result.Value());
   auto log{result.Log()};
   REQUIRE(2 == log.size());
   REQUIRE(message == log[0]);
   REQUIRE(add_message == log[1]);
}