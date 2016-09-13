#include "solipong.h"

void Ball::setRadius(int r){radius = r;}

void Ball::setPosition(float x, float y){ position.x = x; position.y = y;}

void Ball::setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }

void Ball::setVelocityMult(float x) { velocityMult = x; }

void Ball::UpdateBall()
{
		position.x += velocity.x;
		position.y += velocity.y;
}

bool Ball::outBounds() const
{
	return getPosition().y < PADDLE_Y_POS - 5;
}

float Ball::getRadius() const {return radius;}

vector2d Ball::getPosition() const {return position;}

vector2d Ball::getVelocity()const {return velocity;}

float Ball::getVelocityMult() const { return velocityMult; }

Ball Ball::createBall(float posX, float posY, float veloX, float veloY, float radius)
{
	Ball temp;

	temp.position.x = posX;
	temp.position.y = posY;
	temp.velocity.x = veloX;
	temp.velocity.y = veloY;
	temp.radius = radius;

	return temp;
}