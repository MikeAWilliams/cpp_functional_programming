#include <optional>
#include <string>
#include <vector>

template <typename valueType>
class Logger
{
public:
   Logger(valueType value, std::optional<std::string> logMessage = {}) 
      : m_value{std::move(value)}
   {
      if(logMessage)
      {
         m_log.emplace_back(std::move(logMessage.value()));
      }
   }

   Logger(valueType value, std::vector<std::string> oldLog)
      : m_value{std::move(value)}
      , m_log{std::move(oldLog)}
   {
   }
   const valueType& Value() const
   {
      return m_value;
   }

   const std::vector<std::string>& Log() const
   {
      return m_log;
   }
private:
   valueType m_value;
   std::vector<std::string> m_log;
};

template<typename valueType, typename F>
Logger<valueType> transform(const Logger<valueType>& input, F function)
{
   return Logger(function(input.Value()), input.Log());
}