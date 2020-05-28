#pragma once
#include"Def.h"

class Disk
{
public:
	Disk();
	~Disk();
	int disk_write(std::string s, int length); //д��s��ռlength����
	bool disk_read(std::string& s, int length);//��ȡs��length����
	int disk_remove(int start, int end);//��start��end���
	int disk_next(int flag);//�ƶ�����һ�����̿�(flag=0��ֻ�е���ǰ���ڷǿ���λ��ʱ�ƶ���flag��other��������ô����������һ����)
	int disk_move(int m);//�ƶ�����m��(��0��ʼ���)
	void disk_format();
	int nowPtr; //���ڴ��̶�дָ������λ��
	int maxsize; //�����������(�ֽ�)
	int restsize; //����ʣ���������ֽڣ�
	std::string vhard;//���̱���
};