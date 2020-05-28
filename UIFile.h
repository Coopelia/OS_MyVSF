#pragma once
#include"Def.h"
#include"Button.h"

enum FileType { T_DIR, T_FILE };

class UI_File
{
public:
	UI_File();
	void setType(FileType type);
	void setPosition(int x, int y);
	void setScale(float x);
	void setName(String s);
	void setID(int id);
	bool onCilck(RenderWindow* app, Event& e);
	void show(RenderWindow* app);
	FileType type;
	Sprite sIcon;
	Texture tIcon[2];
	Font font;
	Vector2i pos;
	int name_len;
	float scale;
	Text name;
	int id;
};

class UI_path
{
public:
	UI_path();
	void Init(RenderWindow* app);
	void setString(String s);
	void setPosition(int x, int y);
	void show();
	RenderWindow* app;
	Button bt_pathname;
	Text t;
	Font font;
};