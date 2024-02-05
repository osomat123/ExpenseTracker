// ExpenseTracker.cpp : Defines the entry point for the application.
//
#include <OpenXLSX.hpp>
#include <iostream>
#include <iomanip>
#include "Expenses.h"

int main()
{
   const std::string path = "C:\\Users\\tejpu\\Downloads\\statement\\cleaned-statement.xlsx";
   OpenXLSX::XLDocument document{path};
   auto wks = document.workbook().worksheet("Sheet1");
   auto rowRange = wks.rows();

   std::vector<ExpenseTracker::Expense> expenses;
   for (const auto& row : rowRange)
   {
      std::vector<OpenXLSX::XLCellValue> values = row.values();

      if (values[2].type() != OpenXLSX::XLValueType::Empty)
      {
         auto date = values[0].get<std::string>();
         auto descr = values[1].get<std::string>();
         auto amount = (values[2].type() == OpenXLSX::XLValueType::Integer) ? static_cast<float>(values[2].get<int>()) : values[2].get<float>();
         expenses.emplace_back(date, descr, amount);
      }
   }
   document.close();

   for (auto const& expense : expenses)
   {
      std::cout << expense << "\n";
   }

   return 0;
}
