#include "solipong.h"
#include "sfwdraw.h"

bool Box::isBoxColliding(float x, float y)
{
	return position.x < x && x < position.x + width &&
		   position.y < y && y < position.y + height;
}

void Box::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}
void Box::setDimension(int w, int h)
{
	width = w;
	height = h;
}

vector2d Box::getPosition() const
{
	return position;
}
vector2d Box::getDimension() const
{
	vector2d temp;
	temp.x = width;
	temp.y = height;
	return temp;
}

Box Box::CreateBox(float x, float y, int width, int height)
{
	Box b;
	b.position.x = x;
	b.position.y = y;
	b.width = width;
	b.height = height;

	return b;
}

// starts drawing from the bottom left corner
void Box::DrawBox(unsigned color = BLACK, unsigned fill = MAGENTA) const
{
	sfw::drawLine(getPosition().x, getPosition().y, 
		getPosition().x + getDimension().x, getPosition().y, color);					// BOTTOM
	sfw::drawLine(getPosition().x, getPosition().y, 
		getPosition().x, getPosition().y + getDimension().y, color);					// LEFT
	sfw::drawLine(getPosition().x, getPosition().y + getDimension().y,
		getPosition().x + getDimension().x, getPosition().y + getDimension().y, color); // TOP
	sfw::drawLine(getPosition().x + width, getPosition().y,
		getPosition().x + getDimension().x, getPosition().y + getDimension().y, color);	// RIGHT

	//FILL
	if (fill != NONE)
	{
		for (int i = height; i > 1; --i)
		{
			sfw::drawLine(getPosition().x, getPosition().y + i - 1, getPosition().x + getDimension().x - 1, getPosition().y + i - 1, fill);
		}
	}
}

void Box::UpdateBox()
{
	setPosition(sfw::getMouseX(),PADDLE_Y_POS);
	//b.y = sfw::getMouseY();
}