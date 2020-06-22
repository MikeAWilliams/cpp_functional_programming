#include <optional>

// toy functionions
double Add3(double value);
bool IsEven(int value);
std::optional<int> Half(int value);
std::optional<int> AddThreeToOddNumbers(int value);

// simulated real functions
struct Configuration
{
   int searchDepth;
};

std::optional<Configuration> GetConfiguration(bool simulateError, int depth);

class DoesWork
{
};

std::optional<DoesWork> GetDoesWork(const Configuration& config);