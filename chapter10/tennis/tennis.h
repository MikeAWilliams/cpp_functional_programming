#include <tuple>
#include <variant>

namespace tennis {
namespace internal {
   enum class Player
   {
      player1,
      player2
   };

   enum class points
   {
      love,
      fifteen,
      thirty
   };

   struct normalScoring
   {
      points player1Score;
      points player2Score;
   };

   struct fourtyScoring
   {
      Player leader;
      points otherPlayerScore;
   };
}

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

   using GameState = std::variant<internal::normalScoring, internal::fourtyScoring>;

   GameState MakeLoveLoveGame();

   std::tuple<Score, Score> GetScore(const GameState& state);

   GameState ScorePointP1(const GameState& state);
}