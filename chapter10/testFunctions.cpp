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

tl::expected<int, std::string> HalfE(int value)
{
   if(IsEven(value))
   {
      return value / 2;
   }
   return tl::make_unexpected("The value was odd");
}

std::optional<int> AddThreeToOddNumbers(int value)
{
   if(!IsEven(value))
   {
      return 3 + value;
   }
   return {};
}

tl::expected<int, std::string> AddThreeToOddNumbersE(int value)
{
   if(!IsEven(value))
   {
      return 3 + value;
   }
   return tl::make_unexpected("The value was even");
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

tl::expected<Configuration, std::string> GetConfigurationE(const std::string &error, int depth)
{
   if(error.size() > 0)
   {
      return tl::make_unexpected(error);
   }
   return Configuration {depth};
}

tl::expected<DoesWork, std::string> GetDoesWorkE(const Configuration& config)
{
   if(config.searchDepth < 1)
   {
      return tl::make_unexpected(std::string{"The search depth must be >= 1"});
   }
   return DoesWork{};
}