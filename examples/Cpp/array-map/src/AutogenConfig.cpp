// This file is auto-generated by Tabular v0.5.0, DO NOT EDIT!

#include "AutogenConfig.h"
#include <stddef.h>
#include <assert.h>
#include <memory>
#include <fstream>
#include "Utility/Conv.h"
#include "Utility/StringUtil.h"

using namespace std;

#ifndef ASSERT
#define ASSERT assert
#endif


namespace config {

// parse data object from an csv row
int NewbieGuideDefine::ParseFromRow(const vector<StringPiece>& row, NewbieGuideDefine* ptr)
{
    ASSERT(row.size() >= 6);
    ASSERT(ptr != nullptr);
    ptr->Name = parseTextAs<std::string>(row[0]);
    ptr->Type = parseTextAs<std::string>(row[1]);
    ptr->Target = parseTextAs<std::string>(row[2]);
    {
        const auto& array = Split(row[3], TABULAR_ARRAY_DELIM, true);
        for (size_t i = 0; i < array.size(); i++)
        {
            ptr->Accomplishment.push_back(parseTextAs<int16_t>(array[i]));
        }
    }
    {
        const auto& dict = Split(row[4], TABULAR_MAP_DELIM1, true);
        for (size_t i = 0; i < dict.size(); i++)
        {
            const auto& kv = Split(dict[i], TABULAR_MAP_DELIM2, true);
            ASSERT(kv.size() == 2);
            if(kv.size() == 2)
            {
                const auto& key = parseTextAs<std::string>(kv[0]);
                ASSERT(ptr->Goods.count(key) == 0);
                ptr->Goods[key] = parseTextAs<uint32_t>(kv[1]);
            }
        }
    }
    ptr->Description = parseTextAs<std::string>(row[5]);
    return 0;
}


} // namespace config 
