#include "IUserInput.h"

class UserInputCli : public ExpenseTracker::IUserInput
{
public:
   explicit UserInputCli(const std::shared_ptr<ExpenseTracker::MappingInfo>& mappingInfo)
      : IUserInput{ mappingInfo }
   {
   }

   ExpenseTracker::CategorizationInfo getCategorizationInfo(const ExpenseTracker::Expense& expense) override;
};

ExpenseTracker::CategorizationInfo UserInputCli::getCategorizationInfo(const ExpenseTracker::Expense& expense)
{
   const auto getInput = []()
   {
      std::string action;
      while (true)
      {
         std::getline(std::cin, action);
         std::ranges::transform(action, action.begin(), ::toupper);

         if (!action.empty() &&
               (action[0] == 'Y' || action[0] == 'N'))
         {
            break;
         }
      }

      return action;
   };

   ExpenseTracker::CategorizationInfo catInfo;
   catInfo.trackExpense = false;
   catInfo.saveKeyword = false;
   catInfo.category = "";
   catInfo.keyword = "";

   std::cout << expense << "\n";

   std::cout << "Categorize? (y/n): ";
   std::string action = getInput();

   std::string keyword;
   std::string category;
   if (action[0] == 'Y')
   {
      std::cout << "Provide category: ";
      std::getline(std::cin, category);

      catInfo.trackExpense = true;
      catInfo.category = category;

      std::cout << "Add mapping? (y/n): ";
      std::string saveAction = getInput();

      if (saveAction[0] == 'Y')
      {
         std::cout << "Provide keyword: ";
         std::getline(std::cin, keyword);

         catInfo.saveKeyword = true;
         catInfo.keyword = keyword;
      }
      std::cout << "\n";
   }
 
   return catInfo;
}