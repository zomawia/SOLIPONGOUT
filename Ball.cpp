#include "solipong.h"
#include <math.h>

void Ball::setRadius(int r){radius = r;}

void Ball::setPosition(float x, float y){ position.x = x; position.y = y;}

void Ball::setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }

void Ball::setVelocityMult(float x) { velocityMult = x; }

//Box Ball::createCollisionBox(float x, float y, float radius)
//{
//	CollisionBox.setPosition(position.x - radius, position.y - radius);
//	CollisionBox.setDimension(radius * 2, radius * 2);
//}

bool Ball::isColliding(Ball b) const
{
	float distance = sqrt(	((position.x - b.position.x) * (position.x - b.position.x))
							+ ((position.y - b.position.y) * (position.y - b.position.y))
							);

	if (position.x + radius + b.radius > b.position.x
		&&	position.x < b.position.x + radius + b.radius
		&&	position.y + radius + b.radius > b.position.y
		&&	position.y < b.position.y + radius + b.radius)
	{
		return (distance < radius + b.radius);
	}

	else return false;

}

void Ball::doCollision(Ball &b)
{
	//http://ericleong.me/research/circle-circle/

	float distance = sqrt(((position.x - b.position.x) * (position.x - b.position.x))
		+ ((position.y - b.position.y) * (position.y - b.position.y))
	);
	
	float midpointX = (position.x + b.position.x) / 2;
	float midpointY = (position.y + b.position.y) / 2;

	position.x = midpointX + radius * (position.x - b.position.x) / distance;
	position.y = midpointY + radius * (position.y - b.position.y) / distance;
	b.position.x = midpointX + b.radius * (b.position.x - position.x) / distance;
	b.position.y = midpointY + b.radius * (b.position.y - position.y) / distance;

	float normX = (b.position.x - position.x) / distance;
	float normY = (b.position.y - position.y) / distance;

	float force = 2 * (velocity.x * normX + velocity.y * normY - b.velocity.x * normX - b.velocity.y * normY) /
		(radius + b.radius);

	float VectX1 = velocity.x - force * radius * normX;
	float VectY1 = velocity.y - force * radius * normY;
	float VectX2 = b.velocity.x + force * b.radius * normX;
	float VectY2 = b.velocity.y + force * b.radius * normY;
	
	velocity.x = VectX1;
	velocity.y = VectY2;
	b.velocity.x = VectX2;
	b.velocity.y = VectY2;
}

void Ball::UpdateBall()
{
		position.x += velocity.x;
		position.y += velocity.y;
		//CollisionBox.setPosition(position.x - radius, position.y - radius);
}

void Ball::setOut()
{
	out = true;
}

bool Ball::getOut() const
{
	return out;
}

bool Ball::outBounds() const
{
	
	return position.y - radius < PADDLE_Y_POS - radius;
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

void Ball::drawColorBall(float radius) const
{
	//for (int i = radius; i > 1; --i-=12)
	//{
	//	sfw::drawCircle(position.x, position.y, i, i, BLUE);
	//}
}