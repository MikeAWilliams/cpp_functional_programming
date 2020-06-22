#include "tennis.h"

// This is an example sketched out in Functional Programming in C++ by Ivan Cukic chapter 9 section 9.3
// The pattern matcher template is the authors with out understanding or modification from me
template <typename... Ts>
struct patternMatcher : Ts... { using Ts::operator()...;};
template <typename... Ts> patternMatcher(Ts...) -> patternMatcher<Ts...>;

static tennis::internal::points AdvanceScore(tennis::internal::points initialValue);
static tennis::Score Convert(tennis::internal::points value);

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
               result = {Convert(state.player1Score), Convert(state.player2Score)};
            },
            [&](const internal::fourtyScoring& state)
            {
            }
         }, stateArg);
      return result;
   }

   GameState ScorePointP1(const GameState& stateArg)
   {
      GameState result;
      std::visit(
         patternMatcher 
         {
               [&](const internal::normalScoring &state)
               {
                  auto nsResult {state}; 
                  nsResult.player1Score = AdvanceScore(state.player1Score);
                  result = nsResult;
               },
               [&](const internal::fourtyScoring &state)
               {
                  
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