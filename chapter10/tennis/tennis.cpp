#include "tennis.h"

namespace tennis {

   GameState MakeLoveLoveGame()
   {
      return GameState{};
   }

   std::tuple<Score, Score> GetScore(const GameState& state)
   {
      return std::make_tuple(Score::love, Score::love);
   }
}