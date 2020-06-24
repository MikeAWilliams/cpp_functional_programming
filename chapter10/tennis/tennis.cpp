#include "tennis.h"
#include <functional>
#include <iostream>

// This is an example sketched out in Functional Programming in C++ by Ivan Cukic chapter 9 section 9.3
// The pattern matcher template is the authors with out understanding or modification from me
template <typename... Ts>
struct patternMatcher : Ts... { using Ts::operator()...;};
template <typename... Ts> patternMatcher(Ts...) -> patternMatcher<Ts...>;

static tennis::internal::points AdvanceScore(tennis::internal::points initialValue);
static tennis::Score Convert(tennis::internal::points value);
static std::function<void(const tennis::internal::normalScoring& state)> GetNormalScoringFunction(tennis::GameState& result, const int playerIndex);
static std::function<void(const tennis::internal::fourtyScoring& state)> GetFourtyScoringFunction(tennis::GameState& result, const tennis::internal::Player whoScored);
static std::function<void(const tennis::internal::duceScoring& state)> GetDuceScoringFunction(tennis::GameState& result, const tennis::internal::Player whoScored);
static std::function<void(const tennis::internal::advantageScoring& state)> GetAdvantageScoringFunction(tennis::GameState& result, const tennis::internal::Player whoScored);
static int GetOtherPlayerIndex(int playerIndex);
static tennis::internal::Player GetPlayerByIndex(int index);

namespace tennis {

   GameState MakeLoveLoveGame()
   {
      return GameState{};
   }

  

   std::tuple<Score, Score> GetScore(const GameState& stateArg)
   {
      std::tuple<tennis::Score, tennis::Score> result;
      std::visit(
         patternMatcher 
         {
            [&](const internal::normalScoring& state)
            {
               result = {Convert(state.scores[0]), Convert(state.scores[1])};
            },
            [&](const internal::fourtyScoring& state)
            {
               if(internal::Player::player1 == state.leader)
               {
                  result = {tennis::Score::fourty, Convert(state.otherPlayerScore)};
               }
               else
               {
                  result = {Convert(state.otherPlayerScore), tennis::Score::fourty};
               }
            },
            [&](const internal::duceScoring &state)
            {
                  result = {tennis::Score::duce, tennis::Score::duce};
            },
            [&](const internal::advantageScoring &state)
            {
               if(internal::Player::player1 == state.leader)
               {
                  result = {tennis::Score::advantage, tennis::Score::notAdvantage};
               }
               else
               {
                  result = {tennis::Score::notAdvantage, tennis::Score::advantage};
               }
            },
            [&](const internal::victoryScoring &state)
            {
               if(internal::Player::player1 == state.winner)
               {
                  result = {tennis::Score::victory, state.otherPlayerScore};
               }
               else
               {
                  result = {state.otherPlayerScore, tennis::Score::victory};
               }
            }
         }, stateArg);
      return result;
   }

   GameState ScorePointP1(const GameState& stateArg)
   {
      GameState result;
      const int index {0};
      std::visit(
         patternMatcher 
         {
               GetNormalScoringFunction(result, 0),
               GetFourtyScoringFunction(result, internal::Player::player1),
               GetDuceScoringFunction(result, internal::Player::player1),
               GetAdvantageScoringFunction(result, internal::Player::player1),
               [&](const internal::victoryScoring &state)
               {
                  result = state;
               }
         }, stateArg);
      return result;
   }

   GameState ScorePointP2(const GameState& stateArg)
   {
      GameState result;
      std::visit(
         patternMatcher 
         {
               GetNormalScoringFunction(result, 1),
               GetFourtyScoringFunction(result, internal::Player::player2),
               GetDuceScoringFunction(result, internal::Player::player2),
               GetAdvantageScoringFunction(result, internal::Player::player2),
               [&](const internal::victoryScoring &state)
               {
                  result = state;
               }
         }, stateArg);
      return result;
   }
}

static tennis::internal::points AdvanceScore(tennis::internal::points initialValue)
{
   if(tennis::internal::points::love == initialValue)
   {
      return tennis::internal::points::fifteen;
   }
   return tennis::internal::points::thirty;
}

static tennis::Score Convert(tennis::internal::points value)
{
   switch(value)
   {
      case tennis::internal::points::love :
         return tennis::Score::love;
      case tennis::internal::points::fifteen :
         return tennis::Score::fifteen;
      case tennis::internal::points::thirty :
         return tennis::Score::thirty;
      }
      return tennis::Score::love;

}

static std::function<void(const tennis::internal::normalScoring& state)> GetNormalScoringFunction(tennis::GameState& result, const int playerIndex)
{
   return [&result, playerIndex{std::move(playerIndex)}](const tennis::internal::normalScoring& state)
   {
      if(state.scores[playerIndex] != tennis::internal::points::thirty)
      {
         auto nsResult {state}; 
         nsResult.scores[playerIndex] = AdvanceScore(state.scores[playerIndex]);
         result = nsResult;
      }
      else
      {
         tennis::internal::fourtyScoring fsResult;
         fsResult.leader = GetPlayerByIndex(playerIndex);
         fsResult.otherPlayerScore = state.scores[GetOtherPlayerIndex(playerIndex)];
         result = fsResult;
      }
   };
}

static std::function<void(const tennis::internal::fourtyScoring& state)> GetFourtyScoringFunction(tennis::GameState& result, const tennis::internal::Player whoScored)
{
   return [&result, whoScored{std::move(whoScored)}](const tennis::internal::fourtyScoring &state)
   {
      if(whoScored == state.leader)
      {
         tennis::internal::victoryScoring vsResult;
         vsResult.winner = whoScored;
         vsResult.otherPlayerScore = Convert(state.otherPlayerScore);
         result = vsResult;
      }
      else 
      {
         if(tennis::internal::points::thirty == state.otherPlayerScore)
         {
            result = tennis::internal::duceScoring{};
         }
         else
         {
            auto fsResult {state};
            fsResult.otherPlayerScore = AdvanceScore(state.otherPlayerScore);
            result = fsResult;
         }
      }
                  
   };
}

static std::function<void(const tennis::internal::duceScoring& state)> GetDuceScoringFunction(tennis::GameState& result, const tennis::internal::Player whoScored)
{
   return [&result, whoScored{std::move(whoScored)}](const tennis::internal::duceScoring &state)
   {
      result = tennis::internal::advantageScoring {whoScored};
   };
}

static std::function<void(const tennis::internal::advantageScoring& state)> GetAdvantageScoringFunction(tennis::GameState& result, const tennis::internal::Player whoScored)
{
   return [&result, whoScored{std::move(whoScored)}](const tennis::internal::advantageScoring &state)
   {
      if(whoScored == state.leader)
      {
         tennis::internal::victoryScoring vsResult;
         vsResult.winner = whoScored;
         vsResult.otherPlayerScore = tennis::Score::notAdvantage;
         result = vsResult;
      }
      else
      {
         result = tennis::internal::duceScoring{};
      }
   };
}

static int GetOtherPlayerIndex(int playerIndex)
{
   if(0 == playerIndex)
   {
      return 1;
   }
   return 0;
}

static tennis::internal::Player GetPlayerByIndex(int index)
{
   if(0 == index)
   {
      return tennis::internal::Player::player1;
   }
   return tennis::internal::Player::player2;
}