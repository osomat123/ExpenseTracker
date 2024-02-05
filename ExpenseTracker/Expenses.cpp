#include "Expenses.h"

namespace ExpenseTracker
{
   Expense::Expense(std::string date, std::string descr, float amt)
      : mDescr{ descr }
      , mAmt{ amt }
      , mDate{date}
   {
   }
   
   std::ostream& operator<<(std::ostream& os, const Expense& expense)
   {
      os << std::left << std::setw(15) << expense.mDate << std::setw(110) << expense.mDescr << std::setw(50) << expense.mAmt;
      return os;
   }
}
