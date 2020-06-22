#include <tuple>

namespace tennis {

   enum class Score
   {
      love,
      fifteen,
      thirty,
      fourty,
      duce,
      advantage,
      notAdvantage,
      victory
   };

   struct GameState
   {

   };

   GameState MakeLoveLoveGame();

   std::tuple<Score, Score> GetScore(const GameState& state);
}