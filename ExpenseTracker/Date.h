#pragma once
#include <chrono>

namespace ExpenseTracker
{
   // TODO: Support various date formats using strategy pattern
   class Date
   {
   public:
      explicit Date(std::string date);
      friend std::ostream& operator<< (std::ostream& os, const Date& date);

   private:
      std::chrono::year_month_day mDate;
   };
}