#pragma once

#include "constded.h"
#include "solipong.h"

class Menu
{
	int font;
	int xhair;
	float timer;
	
	Box playButton, exitButton;

public:
	void init(int a_font, int a_xhair);
	void play();
	void draw();
	void step();
	
	void DrawButton(Box b, float x, float y, int width, int height, char text[], int color, int fill) const;

	APP_STATE next();
};
