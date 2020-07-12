#include "tennis.h"
#include "tennisLogger.h"

#include <vector>
#include <string>

static std::string GetString(const tennis::Score score);

Logger<tennis::GameState> LogScorePointP1(const tennis::GameState& state)
{
   std::vector<std::string> log;
   log.emplace_back(GetScoreAsString(state));
   log.emplace_back("Player1 scored");

   return Logger(tennis::ScorePointP1(state), log);
}
Logger<tennis::GameState> LogScorePointP2(const tennis::GameState& state)
{
   std::vector<std::string> log;
   log.emplace_back(GetScoreAsString(state));
   log.emplace_back("Player2 scored");

   return Logger(tennis::ScorePointP2(state), log);
}

std::string GetScoreAsString(const tennis::GameState& state)
{
   auto [ p1Score, p2Score] = tennis::GetScore(state);
   if(tennis::Score::duce == p1Score)
   {
      return "Duce";
   }
   if(tennis::Score::advantage == p1Score)
   {
      return "Advantage Player 1";
   }
   if(tennis::Score::advantage == p2Score)
   {
      return "Advantage Player 2";
   }
   return GetString(p1Score) + " " + GetString(p2Score);
}

static std::string GetString(const tennis::Score score)
{
   switch(score)
   {
      case tennis::Score::love:
         return "Love";
      case tennis::Score::fifteen:
         return "Fifteen";
      case tennis::Score::thirty:
         return "Thirty";
      case tennis::Score::fourty:
         return "Fourty";
      case tennis::Score::duce:
         return "Duce";
      case tennis::Score::advantage:
         return "Advantage";
      case tennis::Score::notAdvantage:
         return "notAdvantage";
      case tennis::Score::victory:
         return "Victory";
   }
   return "";
}