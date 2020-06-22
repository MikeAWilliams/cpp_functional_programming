#include "testFunctions.h"

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