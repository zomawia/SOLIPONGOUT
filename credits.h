#pragma once

#include "constded.h"
#include "solipong.h"

class Credits
{
	int font;
	float timer;
	float mover;
	float moverNum;
	float yPos;
	float yCount;

public:
	void init(int a_font);

	void play();
	void draw();
	void step();

	APP_STATE next();
};
