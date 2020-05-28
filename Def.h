#pragma once
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<SFML/Graphics.hpp>
using namespace sf;

#define WIN_WIDTH 1280 //窗口宽
#define WIN_HEIGHT 720 //窗口高
#define ICON_WIDTH 100//图标宽
#define ICON_HEIGHT 100//图标高
#define ICON_SCALE 1//图标大小

#define BLOCKSIZE 1024 //磁盘块大小
#define BLOCKNUM 1000 //磁盘块数量
#define SIZE 1024000 //虚拟磁盘空间大小（字节）
#define END 65535 //FAT中的文件结束标志
#define FREE 0 //FAT中盘块空闲标志
#define ROOTBLOCKNUM 2 //根目录区所占盘块个数
#define MAXSON 10 //最多子目录项

#define BLOCK0SIZE 1//引导块大小

#define FATSIZE 2 //FAT大小

#define FILENAMESIZE 11 //文件名大小（字节）
#define EXNAMESIZE 4 //拓展名大小（字节）
#define ATTRIBUTESIZE 2 //属性数据大小（字节）
#define TIMESIZE 7 //时间数据大小（字节）
#define DATASIZE 9 //日期数据大小（字节）
#define FIRSTSIZE 5 //首块号数据大小（字节）
#define FILELENGTHSIZE 9//文件长度数据大小（字节）
#define FREESIZE 2//目录项分配情况数据大小（字节）
#define NUMSONSIZE 3//目录项个数数据大小（字节）
#define SONSIZE 41//子目录项个数数据大小（字节）
#define FCBSIZE 93//文件控制块大小（字节）