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
	FCB(const FCB& e);//���ƹ��캯��
	void Init(std::string filename, unsigned char attribute, unsigned short first, unsigned long length);
	void add(int a);//�����ʼ�̿��Ϊa��Ŀ¼��
	void remove(int a);//ɾ����ʼ�̿��Ϊa��Ŀ¼��
	int get_now_data();//��ȡ��ǰ����
	int get_now_time();//��ȡ��ǰʱ��
	char filename[FILENAMESIZE]; //�ļ���
	char exname[EXNAMESIZE]; //�ļ���չ��(ͳһΪtxt)
	unsigned char attribute;//�ļ������ֶΣ�Ϊ�����������ֻΪ�ļ��������������ԣ�ֵΪ0 ʱ��ʾĿ¼�ļ���ֵΪ1 ʱ��ʾ�����ļ�
	char m_time[6];//�ļ�����ʱ��
	char m_data[8];//�ļ���������
	unsigned short first;//�ļ���ʼ�̿��
	unsigned long length;//�ļ����ȣ��ֽ�����
	unsigned char free;//��ʾĿ¼���Ƿ�Ϊ�գ���ֵΪ0����ʾ�գ�ֵΪ1����ʾ�ѷ���
	unsigned short num_son;//��ΪĿ¼�ļ������ļ�����
	unsigned short son[MAXSON];//���ļ���ʼ�̿��
};