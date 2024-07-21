#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

namespace ExpenseTracker
{
   struct MappingInfo
   {
      explicit MappingInfo(const std::string& mappingFilePath)
         : mKeywords{}
         , mCategories{}
         , mKeywordToCategoryMap{}
      {
         loadMappingsFromFile(mappingFilePath);
      }

      ~MappingInfo()
      {
         saveMappingToFile();
      }

      void loadMappingsFromFile(std::string filePath);
      void saveMappingToFile();

      std::vector<std::string> mKeywords;
      std::vector<std::string> mCategories;
      std::unordered_map<std::string, std::string> mKeywordToCategoryMap;
   };
}