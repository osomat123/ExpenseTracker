#include "MappingInfo.h"

namespace ExpenseTracker
{
   void MappingInfo::loadMappingsFromFile(std::string filePath)
   {
      std::ifstream file(filePath);

      if (file && file.is_open())
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

            mKeywords.emplace_back(keyword);
            mCategories.emplace_back(category);
            mKeywordToCategoryMap.insert(std::make_pair(keyword, category));
         }
      }
   }

   void MappingInfo::saveMappingToFile()
   {
      std::ofstream file("mapping.txt");

      const auto writeToFile = [&file](const auto& entry)
         {
            file << entry.first << " : " << entry.second << "\n";
         };

      std::ranges::for_each(mKeywordToCategoryMap, writeToFile);
      file.close();
   }
}