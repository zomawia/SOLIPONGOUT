#pragma once

#include "solipong.h"
#include "constded.h"

class BossBall
{
	Ball bossBall;
	//int BossHealth;
	Box laser;
	int font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	float timer;
	BOSS_STATE currentState;

public:
	
	//int getHealth() const;
	Ball getBall();
	
	BossBall create();
	void Draw();
	void FireLasers();
	Box GetLaser() const;
	void Update();
	//void reduceHealth(int damage);
	bool isCollidingWall();
	bool isLaserOut() const;

	void BossBall::init(int a_font);
	void BossBall::reduceHealth(int dmg);

	void setTalk(BOSS_STATE b);
	BOSS_STATE getTalk() const;
	void drawTalk(BOSS_STATE b, int tauntSelect);
};