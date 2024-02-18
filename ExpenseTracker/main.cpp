// main.cpp : Defines the entry point for the application.
//
#include "ExpenseTracker.h"

int main()
{
   const std::string path = "C:\\Users\\tejpu\\Downloads\\statement\\cleaned-statement.xlsx";
   const std::string mappingPath = "C:\\Users\\tejpu\\Downloads\\statement\\mapping.txt";
   ExpenseTracker::ExpenseTracker tracker;

   tracker.loadMappingsFromFile(mappingPath);
   tracker.loadExpensesFromFile(path);
   tracker.categorizeExpenses();
   tracker.printExpenses();

   return 0;
}
