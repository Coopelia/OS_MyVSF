#pragma once
#include"Def.h"

class Button
{
public:
	Button();
	bool PreBehRel; 
	void setTextrue(String s);
	void setPosition(int x, int y);
	void setScale(float x, float y);
	void show();
	bool onClick(Event& e);
	Sprite s;
	Texture t;
	RenderWindow* app;
};