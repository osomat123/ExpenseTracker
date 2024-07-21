// main.cpp : Defines the entry point for the application.
//
#include "ExpenseTracker.h"
#include <UserInputCli.h>

int main()
{
   const std::string path = "C:\\Users\\tejpu\\Downloads\\statement2024\\statement2024.xlsx";
   const std::string mappingPath = "C:\\Users\\tejpu\\Downloads\\statement2024\\mapping.txt";

   std::shared_ptr<ExpenseTracker::MappingInfo> mappingInfo = std::make_shared<ExpenseTracker::MappingInfo>(mappingPath);
   ExpenseTracker::ExpenseTracker tracker{path, mappingInfo, std::make_unique<UserInputCli>(mappingInfo)};

   tracker.categorizeExpenses();
   auto expenseMap = tracker.computeExpensePerCategory();

   std::cout << "Expenses:\n";

   float total = 0;
   for (const auto& [key, value] : expenseMap)
   {
      std::cout<< std::left
               << std::setw(25) << key
               << std::setw(10) << value << "\n";

      total += value;
   }
   std::cout << "Total: " << total;

   tracker.printExpenses();

   return 0;
}
