#pragma once
#include"vfs.h"
#include"UIFile.h"

class UIScene
{
public:
	UIScene();
	void Start();
	void show_now_path();//显示路径
	void show_now_dir();//显示当前所在目录
	void show_now_file();//显示当前打开的数据文件内容
	void show_button();//显示按钮
	void create_dirAfile(std::string s, FileType type);
	void delete_dirAFile();//删除文件
	void open();//打开文件（夹）
	void close();//关闭文件
	void write_file();
	void Input(Event& e);
	void input_path(Event& e);
	void input_txt(Event& e);
	void input_writing(Event& e);
	void input_dir(Event& e);
	void input_naming(Event& e, std::string& s);
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
	Text txt, tip, tName, t_meg;
	Font font;
	int core_x, core_y;//文件视图第一个文件的坐标
	int now_numFile;//当前视图下文件数量
	UI_File now_ls[MAXSON];//当前目录下的目录项
	UI_path upath[10];//路径，这里默认最深10级
	int id_seleted;//当前选中文件id(从左往右,从上往下+1)
	int dx, dy;//文件之间位置间隔；
	std::string now_file_content;//文件内容区（如果打开了数据文件的话）
	std::string s_naming;//正在输入的文件名
	int SceneMode;//1：文件夹，2：文件
	int sta_naming;//0：不在命名状态或输入结束，1：正在输入，2：正在提交
	bool isWriting;//是否正在写入文件数据内容
	FileType nam_type;//新建文件类型
};