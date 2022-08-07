// This file is auto-generated by Tabugen v0.9.1, DO NOT EDIT!
package config

import (
	"log"
	"strconv"
	"strings"
)

var (
	_ = log.Panicf
	_ = strings.Split
	_ = strconv.Itoa
)

//  新手任务.xlsx
type NewbieGuideDefine struct {
	Name           string            // ID
	Type           string            // 任务类型
	Target         string            // 目标
	Accomplishment []int16           // 完成步骤
	Goods          map[string]uint32 // 物品
	Description    string            // 描述
}

func (p *NewbieGuideDefine) ParseFrom(record map[string]string) error {
	p.Name = strings.TrimSpace(record["Name"])
	p.Type = strings.TrimSpace(record["Type"])
	p.Target = strings.TrimSpace(record["Target"])
	if text := record["Accomplishment"]; text != "" {
		var strArr = strings.Split(text, "|")
		var arr = make([]int16, 0, len(strArr))
		for _, s := range strArr {
			var val = parseI16(s)
			arr = append(arr, val)
		}
		p.Accomplishment = arr
	}
	if text := record["Goods"]; text != "" {
		var kvList = strings.Split(text, "|")
		var dict = make(map[string]uint32, len(kvList))
		for _, kv := range kvList {
			if kv != "" {
				var pair = strings.Split(kv, "=")
				var key = strings.TrimSpace(pair[0])
				var val = parseU32(pair[1])
				dict[key] = val
			}
		}
		p.Goods = dict
	}
	p.Description = strings.TrimSpace(record["Description"])
	return nil
}
