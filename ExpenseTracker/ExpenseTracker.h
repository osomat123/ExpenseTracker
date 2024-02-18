#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <OpenXLSX.hpp>
#include "Expense.h"

namespace ExpenseTracker
{
   class ExpenseTracker
   {
   public:
      explicit ExpenseTracker()
         : mExpenses{}
         , mKeywords{}
         , mKeywordToCategoryMap{}
      {
      }

      void loadExpensesFromFile(std::string filePath);
      void loadMappingsFromFile(std::string filePath);
      std::string getExpenseCategory(const Expense & expense);
      void categorizeExpenses();
      void printExpenses();
      void saveMappingToFile();

   private:
      std::vector<Expense> mExpenses;
      std::vector<std::string> mKeywords;
      std::unordered_map<std::string, std::string> mKeywordToCategoryMap;
   };
}