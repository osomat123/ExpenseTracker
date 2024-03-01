// main.cpp : Defines the entry point for the application.
//
#include "ExpenseTracker.h"

int main()
{
   const std::string path = "C:\\Users\\tejpu\\Downloads\\statement\\cleaned-statement.xlsx";
   const std::string mappingPath = "C:\\Users\\tejpu\\Downloads\\statement\\mapping.txt";
   ExpenseTracker::ExpenseTracker tracker;

   // tracker.loadMappingsFromFile(mappingPath);   // Use if you already have a mappings file
   tracker.loadExpensesFromFile(path);
   tracker.categorizeExpenses();
   tracker.saveMappingToFile();  // save the mappings to file

   // Report Generation
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

   //tracker.printExpenses();

   return 0;
}
