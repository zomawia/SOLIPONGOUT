#pragma once

#include "solipong.h"

class BossBall
{
	Ball bossBall;
	int Health;
	Box laser;

public:
	
	int getHealth() const;
	Ball getBall();
	
	BossBall create(BossBall b);
	void Draw();
	void FireLasers();
	void Update();
	void reduceHealth(int damage);
	bool isCollidingWall();
	bool isLaserOut() const;

};