#include "tl/expected.hpp"

#include <optional>
#include <string>

// toy functionions
double Add3(double value);
bool IsEven(int value);
std::optional<int> Half(int value);
tl::expected<int, std::string> HalfE(int value);
std::optional<int> AddThreeToOddNumbers(int value);
tl::expected<int, std::string> AddThreeToOddNumbersE(int value);

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

tl::expected<Configuration, std::string> GetConfigurationE(const std::string &error, int depth);
tl::expected<DoesWork, std::string> GetDoesWorkE(const Configuration& config);