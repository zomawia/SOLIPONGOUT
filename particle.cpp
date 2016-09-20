#include "particle.h"

void Particle::init(int a_font)
{
	Particle par[5] = {};
}

void Particle::play()
{
}

void Particle::draw()
{
	sfw::drawCircle(position.x, position.y, 1, 1, BLACK);
}

void Particle::step()
{
}
