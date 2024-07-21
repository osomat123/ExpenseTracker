 #include "ExpenseTracker.h"

namespace ExpenseTracker
{
   void ExpenseTracker::loadExpensesFromFile(std::string filePath)
   {
      OpenXLSX::XLDocument document{ filePath };
      auto wks = document.workbook().worksheet("Sheet 1");
      auto rowRange = wks.rows();

      for (const auto& row : rowRange)
      {
         std::vector<OpenXLSX::XLCellValue> values = row.values();

         if (/*values[2].type() != OpenXLSX::XLValueType::Empty*/ values.size() == 3)
         {
            auto date = values[0].get<std::string>();
            auto descr = values[1].get<std::string>();
            auto amount = (values[2].type() == OpenXLSX::XLValueType::Integer) ? static_cast<float>(values[2].get<int>()) : values[2].get<float>();

            mExpenses.emplace_back(date, descr, amount);
         }
      }
      document.close();
   }

   void ExpenseTracker::categorizeExpenses()
   {
      for (auto& expense : mExpenses)
      {
         const auto containsKeyword = [expense](const std::string& keyword)
         {
            std::string mainStr(expense.mDescr);
            std::string subStr(keyword);
            std::ranges::transform(expense.mDescr, mainStr.begin(), ::toupper);
            std::ranges::transform(keyword, subStr.begin(), ::toupper);
            return mainStr.find(subStr) != std::string::npos;
         };

         auto result = std::ranges::find_if(mMappingInfo->mKeywords, containsKeyword);

         std::string category;
         if (result == mMappingInfo->mKeywords.end())
         {
            CategorizationInfo catInfo = mUserInput->getCategorizationInfo(expense);
            expense.mIsTracked = catInfo.trackExpense;
            expense.mCategory = catInfo.category;

            if (catInfo.saveKeyword)
            {
               mMappingInfo->mCategories.emplace_back(catInfo.category);
               mMappingInfo->mKeywords.emplace_back(catInfo.keyword);
               mMappingInfo->mKeywordToCategoryMap.insert(std::make_pair(catInfo.keyword, catInfo.category));
            }

         }
         else
         {
            expense.mIsTracked = true;
            expense.mCategory = mMappingInfo->mKeywordToCategoryMap.at(*result);
         }
      }
   }

   void ExpenseTracker::printExpenses()
   {
      float sum = 0;
      for (auto const& expense : mExpenses)
      {
         std::cout << expense << "\n";
      }
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