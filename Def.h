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

#define WIN_WIDTH 1280 //���ڿ�
#define WIN_HEIGHT 720 //���ڸ�
#define ICON_WIDTH 100//ͼ���
#define ICON_HEIGHT 100//ͼ���
#define ICON_SCALE 1//ͼ���С

#define BLOCKSIZE 1024 //���̿��С
#define BLOCKNUM 1000 //���̿�����
#define SIZE 1024000 //������̿ռ��С���ֽڣ�
#define END 65535 //FAT�е��ļ�������־
#define FREE 0 //FAT���̿���б�־
#define ROOTBLOCKNUM 2 //��Ŀ¼����ռ�̿����
#define MAXSON 10 //�����Ŀ¼��

#define BLOCK0SIZE 1//�������С

#define FATSIZE 2 //FAT��С

#define FILENAMESIZE 11 //�ļ�����С���ֽڣ�
#define EXNAMESIZE 4 //��չ����С���ֽڣ�
#define ATTRIBUTESIZE 2 //�������ݴ�С���ֽڣ�
#define TIMESIZE 7 //ʱ�����ݴ�С���ֽڣ�
#define DATASIZE 9 //�������ݴ�С���ֽڣ�
#define FIRSTSIZE 5 //�׿�����ݴ�С���ֽڣ�
#define FILELENGTHSIZE 9//�ļ��������ݴ�С���ֽڣ�
#define FREESIZE 2//Ŀ¼�����������ݴ�С���ֽڣ�
#define NUMSONSIZE 3//Ŀ¼��������ݴ�С���ֽڣ�
#define SONSIZE 41//��Ŀ¼��������ݴ�С���ֽڣ�
#define FCBSIZE 93//�ļ����ƿ��С���ֽڣ�