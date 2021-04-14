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

// 全局数值配置
struct GlobalPropertyDefine 
{
    double                                GoldExchangeTimeFactor1 = 0.0;     // 金币兑换时间参数1
    double                                GoldExchangeTimeFactor2 = 0.0;     // 金币兑换时间参数2
    double                                GoldExchangeTimeFactor3 = 0.0;     // 金币兑换时间参数3
    uint16_t                              GoldExchangeResource1Price = 0;    // 金币兑换资源1价格
    uint16_t                              GoldExchangeResource2Price = 0;    // 金币兑换资源2价格
    uint16_t                              GoldExchangeResource3Price = 0;    // 金币兑换资源3价格
    uint16_t                              GoldExchangeResource4Price = 0;    // 金币兑换资源4价格
    uint16_t                              FreeCompleteSeconds = 0;           // 免费立即完成时间
    uint16_t                              CancelBuildReturnPercent = 0;      // 取消建造后返还资源比例
    bool                                  EnableSearch = false;              // 开启搜索
    std::vector<int>                      SpawnLevelLimit;                   // 最大刷新个数显示
    std::unordered_map<std::string, int>  FirstRechargeReward;               // 首充奖励

    static int ParseFromRows(const std::vector<std::vector<StringPiece>>& rows, GlobalPropertyDefine* ptr);
};

} // namespace config
