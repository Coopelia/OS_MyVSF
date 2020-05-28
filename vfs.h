#pragma once
#include"MyFile.h"
#include"FATFCB.h"
#include"Block0.h"
#include"Button.h"
#include"Disk.h"

class MyFSY
{
public:
	MyFSY();
	void sys_start(std::string m_disk);//根据m_disk初始化文件系统
	void sys_format();//格式化
	int sys_mkdir(std::string dirname);//在当前目录创建文件夹（1：成功，0：子目录项个数满了，-1：重名，其它：空间不足）
	int sys_opendir(FCB fcb);//打开文件夹（1：成功）
	int sys_closedir();//关闭当前打开文件夹，返回到父目录（1：成功）
	int sys_mkfile(std::string filename);//在当前目录创建文件（1：成功，0：子目录项个数满了，-1：重名，其它：空间不足）
	int sys_write_file(FCB& fcb, std::string content);//将content内容写入数据文件（1：成功，0：空间不足，-1：不是数据文件）
	int sys_read_file(FCB fcb, std::string& content);//将fcb对应数据文件内容读到content中（1：成功，-1：不是数据文件）
	void write_byFAT(unsigned short first, std::string content);//根据fat表把content写入磁盘（first是起始盘块号）
	void read_byFAT(unsigned short first, std::string& content);//根据fat表从磁盘把数据写入content（first是起始盘块号）
	void update_fat();//更新disk里的fat
	void write_fcb(FCB fcb);//将FCB写入disk并更新FAT
	void get_fcb(int start, FCB& fcb);//通过起始盘块号start获取FCB
	Block0 initblock;//引导块
	FAT fat1, fat2;//两个FAT表
	mDir nowDir;//当前目录
	Disk disk;//虚拟磁盘
};