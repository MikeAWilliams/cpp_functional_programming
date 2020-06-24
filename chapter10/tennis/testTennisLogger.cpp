#include "catch2/catch.hpp"

#include "tennis.h"
#include "tennisLogger.h"


TEST_CASE("test p1 scores", "[tennis]")
{
   auto gameState{tennis::MakeLoveLoveGame()};

   auto result {LogScorePointP1(gameState)};
}
