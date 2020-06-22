#include "catch2/catch.hpp"

#include "tennis.h"

TEST_CASE("test game init", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};
   auto [ p1Score, p2Score] = tennis::GetScore(gameState);

    REQUIRE(tennis::Score::love == p1Score);
    REQUIRE(tennis::Score::love == p2Score);
}