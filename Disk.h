#pragma once
#include"Def.h"

class Disk
{
public:
	Disk();
	~Disk();
	int disk_write(std::string s, int length); //写入s，占length长度
	bool disk_read(std::string& s, int length);//读取s，length长度
	//int disk_remove(int start, int end);//从start到end清除
	int disk_next(int flag);//移动到下一个磁盘块(flag=0：只有当当前处于非块首位置时移动；flag：other，不管怎么样都往后移一个块)
	int disk_move(int m);//移动到第m块(从0开始编号)
	void disk_format();
	int nowPtr; //现在磁盘读写指针所在位置
	std::string vhard;//磁盘本体
};