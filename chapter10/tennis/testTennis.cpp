#include "catch2/catch.hpp"

#include "tennis.h"

TEST_CASE("test game init", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   auto [ p1Score, p2Score] = tennis::GetScore(gameState);

   REQUIRE(tennis::Score::love == p1Score);
   REQUIRE(tennis::Score::love == p2Score);
}

TEST_CASE("test p1 scores up to thirty", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP1(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);

   REQUIRE(tennis::Score::fifteen == p1Score);
   REQUIRE(tennis::Score::love == p2Score);

   gameState = tennis::ScorePointP1(gameState);

   std::tie(p1Score, p2Score) = tennis::GetScore(gameState);

   REQUIRE(tennis::Score::thirty == p1Score);
   REQUIRE(tennis::Score::love == p2Score);
}

TEST_CASE("test p2 scores up to thirty", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP2(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);

   REQUIRE(tennis::Score::love == p1Score);
   REQUIRE(tennis::Score::fifteen == p2Score);

   gameState = tennis::ScorePointP2(gameState);

   std::tie(p1Score, p2Score) = tennis::GetScore(gameState);

   REQUIRE(tennis::Score::love == p1Score);
   REQUIRE(tennis::Score::thirty == p2Score);
}

TEST_CASE("test both player score to thirty", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);

   REQUIRE(tennis::Score::thirty == p1Score);
   REQUIRE(tennis::Score::thirty == p2Score);
}

TEST_CASE("test p1 scores up to fourty", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);


   REQUIRE(tennis::Score::fourty == p1Score);
   REQUIRE(tennis::Score::love == p2Score);
}

TEST_CASE("test p2 scores up to fourty", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);


   REQUIRE(tennis::Score::love == p1Score);
   REQUIRE(tennis::Score::fourty == p2Score);
}

TEST_CASE("test p1 wins from fourty scoring", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);


   REQUIRE(tennis::Score::victory == p1Score);
   REQUIRE(tennis::Score::love == p2Score);
}

TEST_CASE("test p1 scores while p2 is at fourty", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);

   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);


   REQUIRE(tennis::Score::thirty == p1Score);
   REQUIRE(tennis::Score::fourty == p2Score);
}

TEST_CASE("test p2 scores while p1 is at fourty", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);
   gameState = tennis::ScorePointP1(gameState);

   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);


   REQUIRE(tennis::Score::fourty == p1Score);
   REQUIRE(tennis::Score::thirty == p2Score);
}

TEST_CASE("test p2 wins from fourty scoring", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);
   gameState = tennis::ScorePointP2(gameState);

   auto [ p1Score, p2Score] = tennis::GetScore(gameState);


   REQUIRE(tennis::Score::love == p1Score);
   REQUIRE(tennis::Score::victory == p2Score);
}