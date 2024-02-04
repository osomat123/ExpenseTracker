// ExpenseTracker.cpp : Defines the entry point for the application.
//
#include <OpenXLSX.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;
using namespace OpenXLSX;

int main()
{
   const string path = "C:\\Users\\tejpu\\Downloads\\statement\\cleaned-statement.xlsx";
   XLDocument document = XLDocument(path);
   auto wks = document.workbook().worksheet("Sheet1");
   auto rowRange = wks.rows();

   float sum = 0;
   for (const auto& row : rowRange)
   {
      std::vector<XLCellValue> values = row.values();

      if (values[2].type() != XLValueType::Empty)
      {
         auto date = values[0].get<string>();
         auto descr = values[1].get<string>();
         auto amount = (values[2].type() == XLValueType::Integer) ? static_cast<float>(values[2].get<int>()) : values[2].get<float>();

         sum += amount;
         cout << left << setw(10) << date << setw(110) << descr << setw(50) << amount << "\n";
      }
   }
   cout << "Total Amount Spent: " << sum << "\n";

   document.close();
   return 0;
}