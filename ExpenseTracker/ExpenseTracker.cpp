#include "ExpenseTracker.h"

namespace ExpenseTracker
{
   void ExpenseTracker::loadExpensesFromFile(std::string filePath)
   {
      OpenXLSX::XLDocument document{ filePath };
      auto wks = document.workbook().worksheet("Sheet1");
      auto rowRange = wks.rows();

      for (const auto& row : rowRange)
      {
         std::vector<OpenXLSX::XLCellValue> values = row.values();

         if (values[2].type() != OpenXLSX::XLValueType::Empty)
         {
            auto date = values[0].get<std::string>();
            auto descr = values[1].get<std::string>();
            auto amount = (values[2].type() == OpenXLSX::XLValueType::Integer) ? static_cast<float>(values[2].get<int>()) : values[2].get<float>();

            mExpenses.emplace_back(date, descr, amount);
         }
      }
      document.close();
   }

   void ExpenseTracker::loadMappingsFromFile(std::string filePath)
   {
      std::ifstream file(filePath);

      if (file.is_open())
      {
         std::string line;
         while (std::getline(file, line))
         {
            const auto trimWhitespace = [](const std::string& str)
               {
                  const auto first = str.find_first_not_of(" \t\n\r");
                  const auto last = str.find_last_not_of(" \t\n\r");

                  return str.substr(first, last - first + 1);
               };

            const auto pos = line.find(":");
            const auto keyword = trimWhitespace(line.substr(0, pos));
            const auto category = trimWhitespace(line.substr(pos + 1, line.length() - pos - 1));

            mKeywords.push_back(keyword);

            mKeywordToCategoryMap.insert(std::make_pair(keyword, category));

         }
      }
   }

   // TODO: Separate User Input Logic from categorization
   std::string ExpenseTracker::getExpenseCategory(Expense & expense)
   {
      const auto containsKeyword = [expense](const std::string& keyword)
         {
            std::string mainStr(expense.mDescr);
            std::string subStr(keyword);
            std::ranges::transform(expense.mDescr, mainStr.begin(), ::toupper);
            std::ranges::transform(keyword, subStr.begin(), ::toupper);
            return mainStr.find(subStr) != std::string::npos;
         };

      auto result = std::ranges::find_if(mKeywords, containsKeyword);

      std::string category;
      if (result == mKeywords.end())
      {
         std::cout << expense << "\n";
         std::cout << "A: Add Expense\n";
         std::cout << "M: Mark as Miscellaneous\n";
         std::cout << "S : Skip\n";

         std::string action;
         while (true)
         {
            std::cout << "Your Action: ";
            std::getline(std::cin, action);
            std::ranges::transform(action, action.begin(), ::toupper);

            if (!action.empty() &&
                (action[0] == 'A' || action[0] == 'M' || action[0] == 'S'))
            {
               break;
            }
         }
         
         std::string newKeyword;
         if (action[0] == 'A')
         {
            std::cout << "Provide Keyword: ";
            std::getline(std::cin, newKeyword);

            std::cout << "Provide category: ";
            std::getline(std::cin, category);

            std::cout << "\n";
         }
         else if (action[0] == 'M')
         {
            newKeyword = expense.mDescr;
            category = "Miscellaneous Expense";
         }
         else if (action[0] == 'S')
         {
            expense.mIsTracked = false;
         }

         if (action[0] == 'A' || action[0] == 'M')
         {
            mKeywords.push_back(newKeyword);
            mKeywordToCategoryMap.insert(std::make_pair(newKeyword, category));
         }
      }
      else
      {
         category = mKeywordToCategoryMap.at(*result);
      }

      return category;
   }

   void ExpenseTracker::categorizeExpenses()
   {
      const auto categorizeExpense = [this](Expense& expense)
         {
            std::string category = getExpenseCategory(expense);
            expense.mCategory = category;
         };
      
      std::ranges::for_each(mExpenses, categorizeExpense);
   }

   void ExpenseTracker::printExpenses()
   {
      float sum = 0;
      for (auto const& expense : mExpenses)
      {
         std::cout << expense << "\n";
      }
   }

   void ExpenseTracker::saveMappingToFile()
   {
      std::ofstream file("mapping.txt");

      const auto writeToFile = [&file](const auto& entry)
         {
            file << entry.first << " : " << entry.second << "\n";
         };

      std::ranges::for_each(mKeywordToCategoryMap, writeToFile);
      file.close();
   }

   std::unordered_map<std::string, float> ExpenseTracker::computeExpensePerCategory()
   {
      std::unordered_map<std::string, float> categoryToExpenseMap;

      auto addExpenseAmtTocategory = [&](Expense& expense)
         {
            auto category = expense.mCategory;
            auto amount = expense.mAmt;

            if(expense.mIsTracked)
            {
               auto result = categoryToExpenseMap.find(category);
               if (result != categoryToExpenseMap.end())
               {
                  result->second += amount;
               }
               else
               {
                  categoryToExpenseMap.insert({ category, amount });
               }
            }

         };

      std::ranges::for_each(mExpenses, addExpenseAmtTocategory);

      return categoryToExpenseMap;
   }
}