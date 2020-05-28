#pragma once
#include"Def.h"

 class Block0 //引导块内容
{
public:
	Block0();
	char information[10];//"10101010"（10个字节）
	unsigned short root; //根目录文件的起始盘块号（4个字节）
	unsigned short startblock; //虚拟磁盘上数据区开始位置（4个字节）
};