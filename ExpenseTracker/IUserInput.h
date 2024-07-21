#pragma once

#include <string>
#include "Expense.h"
#include "MappingInfo.h"

namespace ExpenseTracker
{
   struct CategorizationInfo
   {
      bool trackExpense;
      bool saveKeyword;
      std::string category;
      std::string keyword;
   };

   class IUserInput
   {
   public:
      IUserInput(const std::shared_ptr<MappingInfo>& mappingInfo)
         : mMappingInfo{ mappingInfo }
      {
      }

      virtual CategorizationInfo getCategorizationInfo(const Expense& expense) = 0;
      virtual ~IUserInput() = default;

   protected:
      std::weak_ptr<MappingInfo> getMappingInfo()
      {
         return mMappingInfo;
      }

   private:
      std::weak_ptr<MappingInfo> mMappingInfo;
   };
}