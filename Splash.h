#pragma once

#include "constded.h"

class Splash
{
	int font;
	float timer;
	float mover;
	float xPos;
	float xSpot;

public:
	void init(int a_font);

	void play();
	void draw();
	void step();

	APP_STATE next();
};
