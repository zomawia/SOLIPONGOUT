#include "BossBall.h"
#include <cstdio>
#include <string>

void BossBall::init(int a_font) { font = a_font; timer = 5; }

void BossBall::reduceHealth(int dmg) { bossBall.reduceHealth(dmg); }

BOSS_STATE BossBall::getTalk() const
{
	return currentState;
}

void BossBall::drawTalk(BOSS_STATE b, int tauntSelect = 1)
{
	switch (b)
	{
	case IDLE:
		break;

	case TAUNT:		
		switch (tauntSelect)
		{
		case 1:
			sfw::drawString(font, "You are no match for me", bossBall.getPosition().x + bossBall.getRadius(),
				bossBall.getPosition().y - bossBall.getRadius(), 12, 12, 0, ' ', 0xbfbfbf91);
			break;
		case 2:
			sfw::drawString(font, "I'm the best!", bossBall.getPosition().x + bossBall.getRadius(), 
				bossBall.getPosition().y - bossBall.getRadius(),
				12, 12, 0, ' ', 0xbfbfbf91);
			break;
		case 3:
		default:
			sfw::drawString(font, "Prepare to lose", bossBall.getPosition().x + bossBall.getRadius(), 
				bossBall.getPosition().y - bossBall.getRadius(),
				12, 12, 0, ' ', 0xbfbfbf91);
			break;
		}
		break;

	case WEAK:
		sfw::drawString(font, "Oww that hurt!", bossBall.getPosition().x + bossBall.getRadius(),
			bossBall.getPosition().y - bossBall.getRadius(), 12, 12, 0, ' ', 0xbfbfbf91);
		break;

	case DEAD:
		sfw::drawString(font, "I'll be back...", bossBall.getPosition().x + bossBall.getRadius(),
			bossBall.getPosition().y - bossBall.getRadius(), 12, 12, 0, ' ', 0xbfbfbf91);
		break;

	case VICTORY:
		sfw::drawString(font, "Try again?", bossBall.getPosition().x + bossBall.getRadius(),
			bossBall.getPosition().y - bossBall.getRadius(), 12, 12, 0, ' ', 0xbfbfbf91);
		break;

	default: IDLE;
	}
}

void BossBall::setTalk(BOSS_STATE b)
{
	currentState = b;
}

Ball BossBall::getBall()
{
	return bossBall;
}

BossBall BossBall::create()
{
	BossBall temp;
	temp.bossBall = temp.bossBall.createBall(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100, 1, 0, 36);
	temp.bossBall.setHealth(50);
	temp.laser = temp.laser.CreateBox(temp.bossBall.getPosition().x, 
					temp.bossBall.getPosition().y - temp.bossBall.getRadius(), 10, 25);
	temp.font = font;
	return temp;
}

void BossBall::Draw()
{	
	//main circle
	if (bossBall.getHealth() >= 40)	sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius()*(timer / 6), 36, GREEN);
	if (bossBall.getHealth() >= 20)sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius()*(timer / 6) - 1, 36, YELLOW);
	if (bossBall.getHealth() >= -10)sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius()*(timer / 6) - 2, 36, RED);

	//mouth
	sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y-5, bossBall.getRadius()/6 *
		(timer / 6) , 3 , BLACK);

	if (bossBall.getHealth() <= 0)
	{			
		for (int i = 0; i < 10; ++i)
		{
			sfw::drawString(font, "#", bossBall.getPosition().x*sfw::getDeltaTime(),
				bossBall.getPosition().y, 12, 12, 0, ' ', 0xbfbfbf91);
		}
	}

	//health
	//sfw::drawString(font, std::to_string(bossBall.getHealth()).c_str(), bossBall.getPosition().x - bossBall.getRadius()/3,
	//	bossBall.getPosition().y - bossBall.getRadius() * .75, 12, 12, 0, ' ', 0xbfbfbf91);

	//left eye
	sfw::drawLine(bossBall.getPosition().x - 8, bossBall.getPosition().y + 8,
		bossBall.getPosition().x - 22, bossBall.getPosition().y + 16 *
		(timer/6), BLACK);

	//right eye
	sfw::drawLine(bossBall.getPosition().x + 8, bossBall.getPosition().y + 8,
		bossBall.getPosition().x + 22, bossBall.getPosition().y + 16 *
		(timer / 6), BLACK);

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
			* randomRange(50, 350) );	
	}
}

Box BossBall::GetLaser() const { return laser; }

void BossBall::Update()
{
	timer -= sfw::getDeltaTime();
	if (timer < 5) timer = 6;
	
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
