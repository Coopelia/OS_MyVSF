#pragma once
#include"Def.h"
#include"FATFCB.h"

typedef struct mDir//文件夹
{
	FCB fcb;
	int dir_ser;//目录级数，根目录为0，下一级+1
	int dir_first[BLOCKNUM - 5];//从根目录开始各级目录的fcb起始盘块号
}mDir;