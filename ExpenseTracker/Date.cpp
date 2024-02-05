#include "Date.h"
#include <regex>

namespace ExpenseTracker
{
   Date::Date(std::string date)
   {
      std::regex pattern("/");

      // Use std::sregex_token_iterator to iterate over the tokens
      std::sregex_token_iterator it(date.begin(), date.end(), pattern, -1);
      std::sregex_token_iterator end;

      // Create a vector to store the substrings
      std::vector<std::string> dateComponents(it, end);

      auto day = static_cast<unsigned int>(std::stoi(dateComponents[0]));
      auto month = static_cast<unsigned int>(std::stoi(dateComponents[1]));
      auto year = 2000 + std::stoi(dateComponents[2]);

      mDate = std::chrono::year_month_day{std::chrono::year{year},
                                          std::chrono::month{month},
                                          std::chrono::day{day}};
   }
   std::ostream& operator<<(std::ostream& os, const Date& date)
   {
      os << date.mDate;
      return os;
   }
}