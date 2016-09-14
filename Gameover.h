#pragma once
#include "constded.h"
#include "solipong.h"

class Gameover
{
	int font;

public:
	void init(int a_font);

	void play();
	void draw();
	void step();

	APP_STATE next();
};