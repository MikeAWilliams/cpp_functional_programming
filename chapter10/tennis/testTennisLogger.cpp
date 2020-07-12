#include "catch2/catch.hpp"

#include "tennis.h"
#include "tennisLogger.h"


TEST_CASE("test p1 scores", "[tennislog]")
{
   auto initialState{tennis::MakeLoveLoveGame()};

   auto result {LogScorePointP1(initialState)};
   auto [ p1Score, p2Score] = tennis::GetScore(result.Value());

   REQUIRE(tennis::Score::fifteen == p1Score);
   REQUIRE(tennis::Score::love == p2Score);

   auto log{result.Log()};
   REQUIRE(2 == log.size());
   REQUIRE("Love Love" == log[0]);
   REQUIRE("Player1 scored" == log[1]);
}

TEST_CASE("test p2 scores", "[tennislog]")
{
   auto initialState{tennis::MakeLoveLoveGame()};

   auto result {LogScorePointP2(initialState)};
   auto [ p1Score, p2Score] = tennis::GetScore(result.Value());

   REQUIRE(tennis::Score::love == p1Score);
   REQUIRE(tennis::Score::fifteen == p2Score);

   auto log{result.Log()};
   REQUIRE(2 == log.size());
   REQUIRE("Love Love" == log[0]);
   REQUIRE("Player2 scored" == log[1]);
}

TEST_CASE("one last big lazy test", "[tennislog]")
{
   auto initialState{tennis::MakeLoveLoveGame()};

   auto result {LogScorePointP1(initialState)};
   result = mbind(result, LogScorePointP1);
   result = mbind(result, LogScorePointP1);

   result = mbind(result, LogScorePointP2);
   result = mbind(result, LogScorePointP2);
   result = mbind(result, LogScorePointP2);

   auto [ p1Score, p2Score] = tennis::GetScore(result.Value());

   REQUIRE(tennis::Score::duce == p1Score);
   REQUIRE(tennis::Score::duce == p2Score);

   auto log{result.Log()};
   REQUIRE(12 == log.size());

   result = mbind(result, LogScorePointP1);
   log = result.Log();
   REQUIRE(14 == log.size());
   REQUIRE("Duce" == log[12]);

   result = mbind(result, LogScorePointP2);
   log = result.Log();
   REQUIRE(16 == log.size());
   REQUIRE("Advantage Player 1" == log[14]);

   result = mbind(result, LogScorePointP1);
   result = mbind(result, LogScorePointP1);

   std::tie(p1Score, p2Score) = tennis::GetScore(result.Value());
   REQUIRE(tennis::Score::victory == p1Score);
   REQUIRE(tennis::Score::notAdvantage == p2Score);

   log = result.Log();
   REQUIRE(20 == log.size());
   REQUIRE("Advantage Player 1" == log[18]);

   REQUIRE("Victory notAdvantage" == GetScoreAsString(result.Value()));
}