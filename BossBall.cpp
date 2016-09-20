#include "BossBall.h"
#include <cstdio>
#include <string>

void BossBall::init(int a_font) { font = a_font; }

void BossBall::reduceHealth(int dmg) { bossBall.reduceHealth(dmg); }

Ball BossBall::getBall()
{
	return bossBall;
}

BossBall BossBall::create()
{
	BossBall temp;
	temp.bossBall = temp.bossBall.createBall(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100, 1, 0, 36);
	temp.bossBall.setHealth(100);
	temp.laser = temp.laser.CreateBox(temp.bossBall.getPosition().x, 
					temp.bossBall.getPosition().y - temp.bossBall.getRadius(), 10, 25);
	temp.font = font;
	return temp;
}

void BossBall::Draw()
{
	//main circle
	sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius(), 36, GREEN);
	sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius() - 1, 36, GREEN);
	sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius() - 2, 36, GREEN);

	//nose
	sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius()/8, 3 , BLACK);

	//health
	sfw::drawString(font, std::to_string(bossBall.getHealth()).c_str(), bossBall.getPosition().x - bossBall.getRadius()/2,
		bossBall.getPosition().y - bossBall.getRadius() / 3, 12, 12, 0, ' ', 0xbfbfbf91);

	//left eye
	sfw::drawLine(bossBall.getPosition().x - 8, bossBall.getPosition().y + 8,
		bossBall.getPosition().x - 22, bossBall.getPosition().y + 16, BLACK);

	//right eye
	sfw::drawLine(bossBall.getPosition().x + 8, bossBall.getPosition().y + 8,
		bossBall.getPosition().x + 22, bossBall.getPosition().y + 16, BLACK);

	FireLasers();
}

void BossBall::FireLasers()
{
	if (bossBall.getHealth() > 0)
	{
		if (isLaserOut())
		{
			//printf("%f %f", bossBall.getPosition().x, bossBall.getPosition().y);
			laser.setPosition(bossBall.getPosition().x, bossBall.getPosition().y - bossBall.getRadius());
		}

		laser.DrawBox(RED, RED);
		laser.setPosition(laser.getPosition().x, laser.getPosition().y - sfw::getDeltaTime()
			* randomRange(100, 350) );	
	}
}

Box BossBall::GetLaser() const { return laser; }

void BossBall::Update()
{
	if (bossBall.getHealth() > 0)
	{
		bossBall.setPosition(bossBall.getPosition().x + bossBall.getVelocity().x, bossBall.getPosition().y);
		if (isCollidingWall())
		{
			bossBall.setVelocity(-bossBall.getVelocity().x, bossBall.getVelocity().y);
		}
	}
}

bool BossBall::isCollidingWall()
{
	if (bossBall.getPosition().x - bossBall.getRadius() <= 0 || bossBall.getPosition().x + bossBall.getRadius() >= WINDOW_WIDTH)
		return true;
	else return false;
}

bool BossBall::isLaserOut() const
{
	return (laser.getPosition().y <= 0);
}
