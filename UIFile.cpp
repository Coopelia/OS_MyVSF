#include"UIFile.h"

UI_File::UI_File()
{
	this->tIcon[0].loadFromFile("assets/image/�ļ���.png");
	this->tIcon[1].loadFromFile("assets/image/�ļ�.png");
	this->font.loadFromFile("assets/fonts/fSimpleRound.ttf");
	this->name.setFont(font);
	this->name.setCharacterSize(32);
	this->name.setFillColor(Color::White);
	this->pos.x = -100;
	this->pos.y = -100;
	this->scale = 1;
	this->name_len = 0;
	this->type = T_FILE;
	this->id = 0;
}

void UI_File::setType(FileType type)
{
	this->type = type;
}

void UI_File::setPosition(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}

void UI_File::setScale(float x)
{
	this->scale = x;
}

void UI_File::setName(String s)
{
	this->name.setString(s);
	this->name_len = s.getSize();
}

void UI_File::setID(int id)
{
	this->id = id;
}

void UI_File::show(RenderWindow* app)
{
	if (this->type == T_DIR)
		this->sIcon.setTexture(tIcon[0]);
	else 
		this->sIcon.setTexture(tIcon[1]);
	this->sIcon.setScale(scale, scale);
	this->sIcon.setPosition(pos.x, pos.y);
	this->name.setPosition(pos.x + (ICON_WIDTH * scale - name_len * 11) / 2, pos.y + ICON_HEIGHT * scale + 3);
	app->draw(sIcon);
	app->draw(name);
}

UI_path::UI_path()
{
	this->font.loadFromFile("assets/fonts/fSimpleRound.ttf");
	this->t.setFont(font);
	this->t.setFillColor(Color::Black);
	this->t.setCharacterSize(10);
}

void UI_path::Init(RenderWindow* app)
{
	this->app = app;
	this->bt_pathname.app = app;
}

void UI_path::setString(String s)
{
	this->t.setString(s);
}

void UI_path::setPosition(int x, int y)
{
	this->bt_pathname.setPosition(x, y);
	this->t.setPosition(x + 3, y + 2);
}

void UI_path::show()
{
	this->bt_pathname.show();
	this->app->draw(t);
}