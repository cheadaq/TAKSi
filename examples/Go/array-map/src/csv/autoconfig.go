// This file is auto-generated by TAKSi v1.3.0, DO NOT EDIT!
package config

import (
	"encoding/csv"
	"io"
	"log"
	"strings"
)

var (
	_ = io.EOF
	_ = strings.Split
	_ = log.Panicf
)

const (
	KeyNewbieGuideDefineName = "newbie_guide_define"
)

// 新手引导配置, 新手任务.xlsx
type NewbieGuideDefine struct {
	Name           string            // ID
	Type           string            // 任务类型
	Target         string            // 目标
	Accomplishment []int             // 完成步骤
	Goods          map[string]uint32 // 物品
	Description    string            // 描述
}

func (p *NewbieGuideDefine) ParseFromRow(row []string) error {
	if len(row) < 6 {
		log.Panicf("NewbieGuideDefine: row length out of index %d", len(row))
	}
	if row[0] != "" {
		p.Name = row[0]
	}
	if row[1] != "" {
		p.Type = row[1]
	}
	if row[2] != "" {
		p.Target = row[2]
	}
	if row[3] != "" {
		for _, item := range strings.Split(row[3], TAKSI_ARRAY_DELIM) {
			var value = MustParseTextValue("int", item, row[3])
			p.Accomplishment = append(p.Accomplishment, value.(int))
		}
	}
	if row[4] != "" {
		p.Goods = map[string]uint32{}
		for _, text := range strings.Split(row[4], TAKSI_MAP_DELIM1) {
			if text == "" {
				continue
			}
			var items = strings.Split(text, TAKSI_MAP_DELIM2)
			var value = MustParseTextValue("string", items[0], row[4])
			var key = value.(string)
			value = MustParseTextValue("uint32", items[1], row[4])
			var val = value.(uint32)
			p.Goods[key] = val
		}
	}
	if row[5] != "" {
		p.Description = row[5]
	}
	return nil
}

func LoadNewbieGuideDefineList(loader DataSourceLoader) ([]*NewbieGuideDefine, error) {
	buf, err := loader.LoadDataByKey(KeyNewbieGuideDefineName)
	if err != nil {
		return nil, err
	}
	var list []*NewbieGuideDefine
	var r = csv.NewReader(buf)
	for i := 0; ; i++ {
		row, err := r.Read()
		if err == io.EOF {
			break
		}
		if err != nil {
			log.Printf("NewbieGuideDefine: read csv %v", err)
			return nil, err
		}
		var item NewbieGuideDefine
		if err := item.ParseFromRow(row); err != nil {
			log.Printf("NewbieGuideDefine: parse row %d, %s, %v", i+1, row, err)
			return nil, err
		}
		list = append(list, &item)
	}
	return list, nil
}
