#pragma once
#include"Def.h"

typedef struct FAT
{
	unsigned short state[BLOCKNUM];
	FAT() { memset(state, FREE, sizeof(state)); };
} FAT;

class FCB
{
public:
	FCB();
	FCB(const FCB& e);//复制构造函数
	void Init(std::string filename, unsigned char attribute, unsigned short first, unsigned long length);
	void add(int a);//添加起始盘块号为a的目录项
	void remove(int a);//删除起始盘块号为a的目录项
	int get_now_data();//获取当前日期
	int get_now_time();//获取当前时间
	char filename[FILENAMESIZE]; //文件名
	char exname[EXNAMESIZE]; //文件拓展名(统一为txt)
	unsigned char attribute;//文件属性字段：为简单起见，我们只为文件设置了两种属性：值为0 时表示目录文件，值为1 时表示数据文件
	char m_time[6];//文件创建时间
	char m_data[8];//文件创建日期
	unsigned short first;//文件起始盘块号
	unsigned long length;//文件长度（字节数）
	unsigned char free;//表示目录项是否为空，若值为0，表示空，值为1，表示已分配
	unsigned short num_son;//若为目录文件，子文件个数
	unsigned short son[MAXSON];//子文件起始盘块号
};