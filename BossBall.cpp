#include "BossBall.h"

int BossBall::getHealth() const
{
	return Health;
}

Ball BossBall::getBall()
{
	return bossBall;
}

BossBall BossBall::create(BossBall b)
{
	BossBall temp;
	temp.bossBall = temp.bossBall.createBall(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100, 1, 0, 36);
	temp.Health = 100;
	temp.laser = temp.laser.CreateBox(temp.bossBall.getPosition().x, 
					temp.bossBall.getPosition().y - temp.bossBall.getRadius(), 10, 25);

	return temp;
}

void BossBall::Draw()
{
	sfw::drawCircle(bossBall.getPosition().x, bossBall.getPosition().y, bossBall.getRadius(), 36, GREEN);
	FireLasers();
}

void BossBall::FireLasers()
{
	int fireStuff = randomRange(0, 1);
	if (fireStuff == 1)
	{
		if (isLaserOut())
			laser.setPosition(bossBall.getPosition().x, bossBall.getPosition().y - bossBall.getRadius());			

		laser.DrawBox(RED, RED);
		laser.setPosition(laser.getPosition().x, laser.getPosition().y - sfw::getDeltaTime() * 300);
	
	}

}

void BossBall::Update()
{
	bossBall.setPosition(bossBall.getPosition().x + bossBall.getVelocity().x, bossBall.getPosition().y);
	if (isCollidingWall())
	{
		bossBall.setVelocity(-bossBall.getVelocity().x, bossBall.getVelocity().y);
	}


}

void BossBall::reduceHealth(int damage)
{
	Health -= damage;
}

bool BossBall::isCollidingWall()
{
	if (bossBall.getPosition().x - bossBall.getRadius() <= 0 || bossBall.getPosition().x + bossBall.getRadius() >= WINDOW_WIDTH)
		return true;
	else return false;
}

bool BossBall::isLaserOut() const
{
	return (laser.getPosition().x <= 0);
}
