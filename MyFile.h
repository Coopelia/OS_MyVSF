#pragma once
#include"Def.h"
#include"FATFCB.h"

typedef struct mDir//�ļ���
{
	FCB fcb;
	int dir_ser;//Ŀ¼��������Ŀ¼Ϊ0����һ��+1
	int dir_first[BLOCKNUM - 5];//�Ӹ�Ŀ¼��ʼ����Ŀ¼��fcb��ʼ�̿��
}mDir;