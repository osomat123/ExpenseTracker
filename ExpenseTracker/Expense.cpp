#include <iomanip>
#include "Expense.h"

namespace ExpenseTracker
{
   Expense::Expense(std::string date, std::string descr, float amt, std::string category)
      : mDescr{descr}
      , mAmt{amt}
      , mDate{date}
      , mCategory{category}
   {
   }
   
   std::ostream& operator<<(std::ostream& os, const Expense& expense)
   {
      os << std::left 
         << std::setw(15) << expense.mDate 
         << std::setw(110) << expense.mDescr 
         << std::setw(50) << expense.mAmt 
         <<std::setw(20) << expense.mCategory;

      return os;
   }
}
