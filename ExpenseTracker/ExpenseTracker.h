#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <OpenXLSX.hpp>
#include "Expense.h"
#include "MappingInfo.h"
#include "IUserInput.h"

namespace ExpenseTracker
{
   class ExpenseTracker
   {
   public:
      explicit ExpenseTracker(const std::string& expenseFilePath, std::shared_ptr<MappingInfo> mappingInfo, std::unique_ptr<IUserInput> userInput)
         : mExpenses{}
         , mMappingInfo{mappingInfo}
         , mUserInput{std::move(userInput)}
      {
         loadExpensesFromFile(expenseFilePath);
      }

      void loadExpensesFromFile(std::string filePath);
      void categorizeExpenses();
      void printExpenses();
      std::unordered_map<std::string, float> computeExpensePerCategory();

   private:
      std::vector<Expense> mExpenses;
      std::shared_ptr<MappingInfo> mMappingInfo;
      std::unique_ptr<IUserInput> mUserInput;
   };
}