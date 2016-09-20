#pragma once
#include "solipong.h"

class Particle
{
	vector2d position, velocity;

public:
	void init(int a_font);

	void play();
	void draw();
	void step();
};