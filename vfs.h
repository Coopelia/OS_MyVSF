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
	void sys_start(std::string m_disk);//����m_disk��ʼ���ļ�ϵͳ
	void sys_format();//��ʽ��
	int sys_mkdir(std::string dirname);//�ڵ�ǰĿ¼�����ļ��У�1���ɹ���0����Ŀ¼��������ˣ�-1���������������ռ䲻�㣩
	int sys_opendir(FCB fcb);//���ļ��У�1���ɹ���
	int sys_closedir();//�رյ�ǰ���ļ��У����ص���Ŀ¼��1���ɹ���
	int sys_mkfile(std::string filename);//�ڵ�ǰĿ¼�����ļ���1���ɹ���0����Ŀ¼��������ˣ�-1���������������ռ䲻�㣩
	int sys_write_file(FCB& fcb, std::string content);//��content����д�������ļ���1���ɹ���0���ռ䲻�㣬-1�����������ļ���
	int sys_read_file(FCB fcb, std::string& content);//��fcb��Ӧ�����ļ����ݶ���content�У�1���ɹ���-1�����������ļ���
	void write_byFAT(unsigned short first, std::string content);//����fat���contentд����̣�first����ʼ�̿�ţ�
	void read_byFAT(unsigned short first, std::string& content);//����fat��Ӵ��̰�����д��content��first����ʼ�̿�ţ�
	void update_fat();//����disk���fat
	void write_fcb(FCB fcb);//��FCBд��disk������FAT
	void get_fcb(int start, FCB& fcb);//ͨ����ʼ�̿��start��ȡFCB
	Block0 initblock;//������
	FAT fat1, fat2;//����FAT��
	mDir nowDir;//��ǰĿ¼
	Disk disk;//�������
};