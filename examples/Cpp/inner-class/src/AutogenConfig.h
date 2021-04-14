// This file is auto-generated by Tabular v0.5.0, DO NOT EDIT!

#pragma once

#include <stdint.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Utility/Range.h"


namespace config {

// separator used by Tabular
static const char TABULAR_CSV_SEP = ',';       // CSV field separator
static const char TABULAR_CSV_QUOTE = '"';     // CSV field quote
static const char* TABULAR_ARRAY_DELIM = ",";  // array item delimiter
static const char* TABULAR_MAP_DELIM1 = ";";   // map item delimiter
static const char* TABULAR_MAP_DELIM2 = "=";   // map key-value delimiter

// 
struct BoxProbabilityDefine 
{
    struct ProbabilityGoodsDefine 
    {
        std::string  GoodsID;            // 物品1id
        uint32_t     Num = 0;            // 物品1数量
        uint32_t     Probability = 0;    // 物品1概率
    };

    std::string                          ID;                  // ID
    int                                  Total = 0;           // 奖励总数
    int                                  Time = 0;            // 冷却时间
    bool                                 Repeat = false;      // 是否可重复
    std::vector<ProbabilityGoodsDefine>  ProbabilityGoods    ; //

    static int ParseFromRow(const std::vector<StringPiece>& row, BoxProbabilityDefine* ptr);
};

} // namespace config
