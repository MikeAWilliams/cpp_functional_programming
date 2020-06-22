#include "testFunctions.h"

// toy functions

double Add3(double value)
{
   return value + 3;
}

bool IsEven(int value)
{
   return value % 2 == 0;
}

std::optional<int> Half(int value)
{
   if(IsEven(value))
   {
      return value / 2;
   }
   return {};
}

std::optional<int> AddThreeToOddNumbers(int value)
{
   if(!IsEven(value))
   {
      return 3 + value;
   }
   return {};
}

// simulated real functions


std::optional<Configuration> GetConfiguration(bool simulateError, int depth)
{
   if(simulateError)
   {
      return {};
   }
   return Configuration {depth};
}

std::optional<DoesWork> GetDoesWork(const Configuration& config)
{
   if(config.searchDepth < 1)
   {
      return {};
   }
   return DoesWork{};
}