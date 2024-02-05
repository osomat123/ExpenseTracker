#pragma once
#include <string>
#include <chrono>
#include"Date.h"

namespace ExpenseTracker
{
   class Expense
   {
   public:
      explicit Expense(std::string date, std::string descr, float amt);
      friend std::ostream& operator<<(std::ostream& os, const Expense& expense);

   private:
      Date mDate;
      std::string mDescr;
      float mAmt;
   };
}

