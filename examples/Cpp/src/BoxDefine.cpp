﻿// This file is auto-generated by Tabular v0.9.1, DO NOT EDIT!

#include "BoxDefine.h"
#include <stddef.h>
#include <assert.h>
#include <memory>
#include <fstream>
#include "Conv.h"
#include "StringUtil.h"

using namespace std;

#ifndef ASSERT
#define ASSERT assert
#endif


namespace config {

// parse BoxProbabilityDefine from string fields
int BoxProbabilityDefine::ParseFrom(const std::unordered_map<std::string, std::string>& record, BoxProbabilityDefine* ptr)
{
    ASSERT(ptr != nullptr);
    std::unordered_map<std::string, std::string>::const_iterator iter;
    iter = record.find("ID");
    if (iter != record.end()) {
        ptr->ID = StripWhitespace(iter->second).as_string();
    }
    iter = record.find("Total");
    if (iter != record.end()) {
        ptr->Total = ParseInt32(iter->second);
    }
    iter = record.find("Time");
    if (iter != record.end()) {
        ptr->Time = ParseInt32(iter->second);
    }
    iter = record.find("Repeat");
    if (iter != record.end()) {
        ptr->Repeat = ParseBool(iter->second);
    }
    for (size_t i = 1; i <= record.size(); i++)
    {
        BoxProbabilityDefine::ProbabilityGoodsDefine val;
        {
            auto key = StringPrintf("GoodsID%d", i);
            auto iter = record.find(key);
            if (iter != record.end()) {
                val.GoodsID = StripWhitespace(iter->second).as_string();
            } else {
                break;
            }
        }
        {
            auto key = StringPrintf("Num%d", i);
            auto iter = record.find(key);
            if (iter != record.end()) {
                val.Num = ParseUInt32(iter->second);
            } else {
                break;
            }
        }
        {
            auto key = StringPrintf("Probability%d", i);
            auto iter = record.find(key);
            if (iter != record.end()) {
                val.Probability = ParseUInt32(iter->second);
            } else {
                break;
            }
        }
        ptr->ProbabilityGoods.push_back(val);
    }
    ptr->ProbabilityGoods.shrink_to_fit();
    return 0;
}


} // namespace config 
