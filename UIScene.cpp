#include"UIScene.h"

UIScene::UIScene()
{
	app = new RenderWindow(VideoMode(1280, 720), L"虚拟文件系统", Uint32(5));
	core_x = 50;
	core_y = 100;
	dx = 130;
	dy = 150;
	now_numFile = 0;
	SceneMode = 1;
	id_seleted = -1;
	sta_naming = 0;
	isWriting = false;
	font.loadFromFile("assets/fonts/oil.ttf");
	txt.setFont(font);
	txt.setFillColor(Color::Black);
	txt.setCharacterSize(30);
	txt.setPosition(50, 100);
	tip.setFont(font);
	tip.setFillColor(Color::Red);
	tip.setCharacterSize(20);
	tip.setPosition(380, 383);
	tName.setFont(font);
	tName.setFillColor(Color::Black);
	tName.setCharacterSize(36);
	tName.setPosition(340, 338);
	t_meg.setFont(font);
	t_meg.setFillColor(Color(125, 125, 125, 255));
	t_meg.setCharacterSize(20);
	t_meg.setPosition(40, 688);
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
		if (!flag)
			vfs.sys_start(str);//初始化
	}
	fin.close();

	this->app->setFramerateLimit(30);
	this->sBackground.setPosition(0, 0);
	this->sBg_dir.setPosition(30, 90);
	this->sBg_txt.setPosition(30, 90);
	this->sBg_path.setPosition(30, 60);
	this->sBg_new.setPosition(200, 300);
	this->bt_cancel.app = app;
	this->bt_cancel.setPosition(880, 336);
	this->bt_close.app = app;
	this->bt_close.setPosition(230, 10);
	this->bt_delete.app = app;
	this->bt_delete.setPosition(450, 10);
	this->bt_newDir.app = app;
	this->bt_newDir.setPosition(168, 10);
	this->bt_newTxt.app = app;
	this->bt_newTxt.setPosition(310, 10);
	this->bt_open.app = app;
	this->bt_open.setPosition(30, 10);
	this->bt_ok.app = app;
	this->bt_ok.setPosition(810, 336);
	this->bt_save.app = app;
	this->bt_save.setPosition(110, 10);
	this->bt_edit.app = app;
	this->bt_edit.setPosition(30, 10);
}

void UIScene::show_now_path()
{
	for (int i = 0; i <= vfs.nowDir.dir_ser; i++)
	{
		upath[i].show();
		upath[i].bt_pathname.reset();
	}
}

void UIScene::show_now_dir()
{
	app->draw(sBg_dir);
	app->draw(sHightLight);
	for (int i = 0; i < now_numFile; i++)
		now_ls[i].show(app);
}

void UIScene::show_now_file()
{
	app->draw(sBg_txt);
	app->draw(txt);
}

void UIScene::show_button()
{
	if (SceneMode == 1)
	{
		if (sta_naming == 0)
		{
			show_now_path();
			bt_open.show();
			bt_newDir.show();
			bt_newTxt.show();
			bt_delete.show();
		}
		else
		{
			app->draw(sBg_new);
			bt_ok.show();
			bt_cancel.show();
			app->draw(tip);
			app->draw(tName);
		}
	}
	else if (SceneMode == 2)
	{
		if (isWriting)
			bt_save.show();
		else
			bt_edit.show();
		bt_close.show();
	}
	bt_cancel.reset();
	bt_close.reset();
	bt_delete.reset();
	bt_edit.reset();
	bt_newDir.reset();
	bt_ok.reset();
	bt_open.reset();
	bt_save.reset();
}

void UIScene::create_dirAfile(std::string s, FileType type)
{
	int ret;
	if (type == T_DIR)
		ret = vfs.sys_mkdir(s);
	else if (type == T_FILE)
		ret = vfs.sys_mkfile(s);
	else return;
	if (ret == 1)
		sta_naming = 0;
	else if (ret == 0)
	{
		sta_naming = 1;
		tip.setString(L"创建失败，子目录项个数满了");
	}
	else if (ret == -1)
	{
		sta_naming = 1;
		tip.setString(L"创建失败，重名了");
	}
	else
	{
		sta_naming = 1;
		tip.setString(L"创建失败，磁盘剩余空间不足");
	}
}

void UIScene::delete_dirAFile()
{
	FCB fcb;
	vfs.get_fcb(vfs.nowDir.fcb.son[id_seleted], fcb);
	vfs.sys_delete(fcb);
	id_seleted = -1;
}

void UIScene::open()
{
	FCB fcb;
	vfs.get_fcb(vfs.nowDir.fcb.son[id_seleted], fcb);
	if (fcb.attribute == '0')
	{
		vfs.nowDir.fcb = fcb;
		vfs.nowDir.dir_first[++vfs.nowDir.dir_ser] = fcb.first;
		SceneMode = 1;
		id_seleted = -1;
	}
	else
	{
		now_file_content.clear();
		if (vfs.sys_read_file(fcb, now_file_content) == 1)
		{
			std::stringstream ss;
			for (int i = 0;  i< now_file_content.length(); i++)
			{
				ss << now_file_content[i];
				if (i % 100 == 0 && i != 0)
					ss << std::endl;
			}
			std::string str;
			ss >> str;
			txt.setString(str);
		}
		SceneMode = 2;
	}
}

void UIScene::close()
{
	now_file_content.clear();
	SceneMode = 1;
	isWriting = false;
	id_seleted = -1;
}

void UIScene::write_file()
{
	FCB fcb;
	vfs.get_fcb(vfs.nowDir.fcb.son[id_seleted], fcb);
	vfs.sys_write_file(fcb, now_file_content);
}

void UIScene::input_writing(Event& e)
{
	std::stringstream ss;
	int i;
	for (i = 0; i < now_file_content.length(); i++)
		ss << now_file_content[i];
	if (e.type == Event::TextEntered)
		if (e.text.unicode >= 33 && e.text.unicode <= 126)
			ss << static_cast<char>(e.text.unicode);
	ss >> now_file_content;
	if (e.type == Event::KeyReleased && e.key.code == Keyboard::BackSpace && now_file_content.length() > 0)
		now_file_content.pop_back();
	txt.setString(now_file_content);
}

void UIScene::input_path(Event& e)
{
	for (int i = 0; i < vfs.nowDir.dir_ser; i++)
	{
		if (upath[i].bt_pathname.onClick(e))
		{
			FCB fcb;
			vfs.get_fcb(vfs.nowDir.dir_first[i], fcb);
			vfs.nowDir.fcb = fcb;
			vfs.nowDir.dir_ser = i;
			id_seleted = -1;
			break;
		}
	}
}

void UIScene::input_dir(Event& e)
{
	for (int i = 0; i < now_numFile; i++)
	{
		if (now_ls[i].onCilck(app, e))
			id_seleted = now_ls[i].id;
	}
	if (id_seleted != -1)
	{
		if(bt_delete.onClick(e))
			delete_dirAFile();
		if (bt_open.onClick(e))
			open();
	}
}

void UIScene::input_txt(Event& e)
{
	if (bt_edit.onClick(e))
		isWriting = true;
	if (bt_save.onClick(e))
	{
		write_file();
		isWriting = false;
	}
	if (bt_close.onClick(e))
		close();
}

void UIScene::input_naming(Event& e, std::string& s)
{
	if (e.type == Event::TextEntered)
		if (e.text.unicode >= 33 && e.text.unicode <= 126)
		{
			if (s.length() >= 10)
				tip.setString(L"文件最大长度只能为10！");
			else
			{
				tip.setString("");
				s += static_cast<char>(e.text.unicode);
			}
		}
	if (e.type == Event::KeyReleased && e.key.code == Keyboard::BackSpace && s.length() > 0)
		s.pop_back();
	if (bt_ok.onClick(e))
		sta_naming = 2;
	if (bt_cancel.onClick(e))
		sta_naming = 0;
}

void UIScene::Input(Event& e)
{
	if (e.type == Event::Closed)
		app->close();
	if (SceneMode == 1)
	{
		input_dir(e);
		if (sta_naming == 0)
		{
			if (bt_newTxt.onClick(e))
			{
				nam_type = T_FILE;
				sta_naming = 1;
				s_naming.clear();
				tip.setString("");
			}
			if (bt_newDir.onClick(e))
			{
				nam_type = T_DIR;
				sta_naming = 1;
				s_naming.clear();
				tip.setString("");
			}
		}
		else if (sta_naming == 1)
			input_naming(e, s_naming);
	}
	else if (SceneMode == 2)
	{
		input_txt(e);
		if (isWriting)
			input_writing(e);
	}
	if (sta_naming == 0)
		input_path(e);
	e.type = Event::Count;
}

void UIScene::update_dir()
{
	FCB fcb;
	now_numFile = 0;
	for (int i = 0; i < vfs.nowDir.fcb.num_son; i++)
	{
		vfs.get_fcb(vfs.nowDir.fcb.son[i], fcb);
		std::string str;
		for (int i = 0; fcb.filename[i] != '\0'; i++)
			str.push_back(fcb.filename[i]);
		if (fcb.attribute == '0')
			now_ls[i].setType(T_DIR);
		else
		{
			now_ls[i].setType(T_FILE);
			str += ".txt";
		}
		now_ls[i].setName(str);
		now_ls[i].id = i;
		now_ls[i].setScale(ICON_SCALE);
		now_ls[i].setPosition(core_x + (i % 10) * dx, core_y + (i / 10) * dy);
		now_numFile++;
	}
	for (int i = 0; i <= vfs.nowDir.dir_ser; i++)
	{
		vfs.get_fcb(vfs.nowDir.dir_first[i], fcb);
		upath[i].Init(app);
		upath[i].setString(fcb.filename);
		upath[i].setPosition(i * 100 + 30, 62);
	}
	if (id_seleted != -1)
	{
		sHightLight.setPosition(core_x + (id_seleted % 10) * dx - 5, core_y + (id_seleted / 10) * dy - 5);
		vfs.get_fcb(vfs.nowDir.fcb.son[id_seleted], fcb);
		std::string str;
		for (int i = 0; i < 8; i++)
		{
			str.push_back(fcb.m_data[i]);
			if (i == 3 || i == 5)
				str.push_back('/');
		}
		str.push_back(' ');
		for (int i = 0; i < 6; i++)
		{
			str.push_back(fcb.m_time[i]);
			if (i == 1 || i == 3)
				str.push_back(':');
		}
		t_meg.setString(L"选中一个文件 修改日期：" + str);
	}
	else
	{
		sHightLight.setPosition(-300, -300);
		t_meg.setString("");
	}
}

void UIScene::Update()
{
	update_dir();
	if (sta_naming == 2)
		create_dirAfile(s_naming, nam_type);
	tName.setString(s_naming);
}

void UIScene::Draw()
{
	app->draw(sBackground);
	if (SceneMode == 1)
		show_now_dir();
	else if (SceneMode == 2)
		show_now_file();
	app->draw(sBg_path);
	show_button();
	app->draw(t_meg);

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