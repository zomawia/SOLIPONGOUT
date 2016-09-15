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
	sfw::drawLine(position.x, position.y, position.x + width, position.y, color);					// BOTTOM
	sfw::drawLine(position.x, position.y, position.x, position.y + height, color);					// LEFT
	sfw::drawLine(position.x, position.y + height, position.x + width, position.y + height, color); // TOP
	sfw::drawLine(position.x + width, position.y, position.x + width, position.y + height, color);	// RIGHT

	//FILL
	if (fill != NONE)
	{
		for (int i = height; i > 1; --i)
		{
			sfw::drawLine(position.x, position.y + i - 1, position.x + width - 1, position.y + i - 1, fill);
		}
	}
}

void Box::UpdateBox()
{
	setPosition(sfw::getMouseX(),PADDLE_Y_POS);
}