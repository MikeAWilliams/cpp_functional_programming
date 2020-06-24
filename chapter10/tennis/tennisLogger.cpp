#include "tennis.h"
#include "tennisLogger.h"

#include <vector>
#include <string>

Logger<tennis::GameState> LogScorePointP1(const tennis::GameState& state)
{
   std::vector<std::string> log;
   log.emplace_back(GetScoreAsString(state));
   log.emplace_back("Player 1 scored");

   return Logger(tennis::ScorePointP1(state), log);
}
Logger<tennis::GameState> LogScorePointP2(const tennis::GameState& state)
{
   std::vector<std::string> log;
   log.emplace_back(GetScoreAsString(state));
   log.emplace_back("Player 2 scored");

   return Logger(tennis::ScorePointP2(state), log);
}

std::string GetScoreAsString(tennis::GameState)
{
   return "";
}