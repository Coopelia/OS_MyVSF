#include"UIScene.h"

UIScene::UIScene()
{
	app = new RenderWindow(VideoMode(1280, 720), L"虚拟文件系统", Uint32(5));
	core_x = 150;
	core_y = 100;
	dx = 250;
	dy = 250;
	now_numFile = 0;
	SceneMode = 1;
	id_seleted = -1;
	font.loadFromFile("assets/fonts/fSimpleRound.ttf");
	txt.setFont(font);
	txt.setFillColor(Color::Black);
	txt.setCharacterSize(30);
	txt.setPosition(50, 100);
	tHightLight.loadFromFile("assets/image/hl.png");
	sHightLight.setTexture(tHightLight);
	tBackground.loadFromFile("assets/image/back.png");
	sBackground.setTexture(tBackground);
	tBg_dir.loadFromFile("assets/image/bg_dir.png");
	sBg_dir.setTexture(tBg_dir);
	tBg_new.loadFromFile("assets/image/bg_new.png");
	sBg_new.setTexture(tBg_new);
	tBg_path.loadFromFile("assets/image/bg_path.png");
	sBg_path.setTexture(tBg_path);
	tBg_txt.loadFromFile("assets/image/bg_txt.png");
	sBg_txt.setTexture(tBg_txt);
	bt_cancel.setTextrue("assets/image/cancel.png");
	bt_close.setTextrue("assets/image/关闭.png");
	bt_delete.setTextrue("assets/image/删除.png");
	bt_newDir.setTextrue("assets/image/新建文件夹.png");
	bt_newTxt.setTextrue("assets/image/新建文件.png");
	bt_ok.setTextrue("assets/image/ok.png");
	bt_open.setTextrue("assets/image/打开.png");
	bt_save.setTextrue("assets/image/保存.png");
	bt_edit.setTextrue("assets/image/edit.png");
}

void UIScene::Start()
{
	//从硬盘中读取文件系统，如果没有就创一个
	std::ifstream fin("assets/myvfs.txt", std::ios::in);
	if (!fin.is_open())
	{
		std::cout << "没有找到系统，将创建一个新系统\n";
		vfs.sys_format();
		std::cout << "创建成功！\n";
	}
	else
	{
		std::cout << "找到文件系统\n";
		std::string str;
		char ct[8];
		bool flag = false;
		str.resize(SIZE);
		for (int i = 0; i < SIZE; i++)
		{
			fin >> str[i];
			if (i == 7)
			{
				if (strcmp(str.c_str(), "10101010") != 0)
				{
					std::cout << "不是合法的文件系统，将创建一个新系统\n";
					vfs.sys_format();
					std::cout << "创建成功！\n";
					flag = true;
					break;
				}
			}
		}
		if(!flag)
			vfs.sys_start(str);//初始化
	}
	fin.close();

	this->app->setFramerateLimit(60);
	this->sBackground.setPosition(0, 0);
	this->sBg_dir.setPosition(30, 90);
	this->sBg_txt.setPosition(30, 90);
	this->sBg_path.setPosition(30, 70);
	this->sBg_new.setPosition(200, 300);
	this->bt_cancel.app = app;
	this->bt_cancel.setPosition(800, 320);
	this->bt_close.app = app;
	this->bt_close.setPosition(100, 10);
	this->bt_delete.app = app;
	this->bt_delete.setPosition(300, 10);
	this->bt_newDir.app = app;
	this->bt_newDir.setPosition(100, 10);
	this->bt_newTxt.app = app;
	this->bt_newTxt.setPosition(200, 10);
	this->bt_open.app = app;
	this->bt_open.setPosition(30, 10);
	this->bt_ok.app = app;
	this->bt_ok.setPosition(700, 320);
	this->bt_save.app = app;
	this->bt_save.setPosition(30, 10);
	this->bt_edit.app = app;
	this->bt_edit.setPosition(30, 10);
}

void UIScene::show_now_path()
{
	for (int i = 0; i <= vfs.nowDir.dir_ser; i++)
		upath[i].show();
}

void UIScene::show_now_dir()
{
	app->draw(sBg_dir);
	bt_open.show();
	bt_newDir.show();
	bt_newTxt.show();
	bt_delete.show();
	app->draw(sHightLight);
	for (int i = 0; i < now_numFile; i++)
		now_ls[i].show(app);
}

void UIScene::show_now_file()
{
	FCB fcb;
	vfs.get_fcb(id_seleted, fcb);
	now_file_content.clear();
	vfs.sys_read_file(fcb, now_file_content);
	txt.setString(now_file_content);
	app->draw(sBg_txt);
	app->draw(txt);
}

void UIScene::create_dir()
{
	std::string name = "test1";
	int ret = vfs.sys_mkdir(name);
	if (ret == 1)
		std::cout << "创建了一个文件夹\n";
	else if (ret == 0)
		std::cout << "创建失败，子目录项个数满了\n";
	else if (ret == -1)
		std::cout << "创建失败，重名了\n";
	else
		std::cout << "创建失败，磁盘剩余空间不足\n";
}

void UIScene::create_file()
{
	std::string name = "test1";
	int ret = vfs.sys_mkfile(name);
	if (ret == 1)
		std::cout << "创建了一个文件\n";
	else if (ret == 0)
		std::cout << "创建失败，子目录项个数满了\n";
	else if (ret == -1)
		std::cout << "创建失败，重名了\n";
	else
		std::cout << "创建失败，磁盘剩余空间不足\n";
}

void UIScene::write_file()
{

}


void UIScene::Input(Event& e)
{
	if (e.type == Event::Closed)
		app->close();
	if (bt_newTxt.onClick(e))
		create_file();
	if (bt_newDir.onClick(e))
		create_dir();
}

void UIScene::update_dir()
{
	FCB fcb;
	now_numFile = 0;
	for (int i = 0; i < vfs.nowDir.fcb.num_son; i++)
	{
		vfs.get_fcb(vfs.nowDir.fcb.son[i], fcb);
		if (fcb.attribute == '0')
			now_ls[i].setType(T_DIR);
		else
			now_ls[i].setType(T_FILE);
		now_ls[i].setName(fcb.filename);
		now_ls[i].setScale(ICON_SCALE);
		now_ls[i].setPosition(core_x + (i % 4) * dx, core_y + (i / 4) * dy);
		now_numFile++;
	}
	for (int i = 0; i <= vfs.nowDir.dir_ser; i++)
	{
		vfs.get_fcb(vfs.nowDir.dir_first[i], fcb);
		upath[i].Init(app);
		upath[i].setString(fcb.filename);
		upath[i].setPosition(i * 50 + 30, 50);
	}
	if (id_seleted != -1)
		sHightLight.setPosition(core_x + (id_seleted % 4) * dx - 5, core_y + (id_seleted / 4) * dy - 5);
	else
		sHightLight.setPosition(-300, -300);
}

void UIScene::Update()
{
	update_dir();
}

void UIScene::Draw()
{
	app->draw(sBackground);
	if (SceneMode == 1)
		show_now_dir();
	else if (SceneMode == 2)
		show_now_file();
	app->draw(sBg_path);
	show_now_path();

	app->display();
}

void UIScene::Exit()
{
	//将内存中的文件系统保存到硬盘
	std::ofstream fout("assets/myvfs.txt", std::ios::trunc);
	for (int i = 0; i < SIZE; i++)
		fout << vfs.disk.vhard[i];
	fout.close();
	delete app;
}

void UIScene::run()
{
	Start();
	while (app->isOpen())
	{
		Event e;
		app->pollEvent(e);
		Update();
		Draw();
		Input(e);
	}
	Exit();
}