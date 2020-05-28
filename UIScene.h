#pragma once
#include"vfs.h"
#include"UIFile.h"

class UIScene
{
public:
	UIScene();
	void Start();
	void show_now_path();//��ʾ·��
	void show_now_dir();//��ʾ��ǰ����Ŀ¼
	void show_now_file();//��ʾ��ǰ�򿪵������ļ�����
	void create_dir();
	void create_file();
	void write_file();
	void Input(Event& e);
	void input_txt(Event& e);
	void input_dir(Event& e);
	void Update();
	void update_dir();
	void Draw();
	void Exit();
	void run();
	MyFSY vfs;
	RenderWindow* app;
	Sprite sBackground, sBg_dir, sBg_txt, sBg_new, sBg_path, sHightLight;
	Texture tBackground, tBg_dir, tBg_txt, tBg_new, tBg_path, tHightLight;
	Button bt_ok, bt_cancel, bt_open, bt_close, bt_delete, bt_save, bt_newDir, bt_newTxt, bt_edit;
	Text txt;
	Font font;
	int core_x, core_y;//�ļ���ͼ��һ���ļ�������
	int now_numFile;//��ǰ��ͼ���ļ�����
	UI_File now_ls[MAXSON];//��ǰĿ¼�µ�Ŀ¼��
	UI_path upath[10];//·��������Ĭ������10��
	int id_seleted;//��ǰѡ���ļ�id(��������,��������+1)
	int dx, dy;//�ļ�֮��λ�ü����
	std::string now_file_content;//�ļ���������������������ļ��Ļ���
	int SceneMode;//1���ļ��У�2���ļ�
};