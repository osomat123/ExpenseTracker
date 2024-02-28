#pragma once
#include <string>
#include <chrono>
#include"Date.h"

namespace ExpenseTracker
{
   struct Expense
   {
      explicit Expense(std::string date, std::string descr, float amt, std::string category="");

      Date mDate;
      bool mIsTracked;
      std::string mDescr;
      float mAmt;
      std::string mCategory;
   };
   std::ostream& operator<<(std::ostream& os, const Expense& expense);
}

