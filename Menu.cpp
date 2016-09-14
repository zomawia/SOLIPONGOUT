#include "Menu.h"
#include <cstdio>

void Menu::init(int a_font, int a_xhair)
{ 
	font = a_font; 
	xhair = a_xhair; 

	playButton.setPosition(WINDOW_WIDTH*.35, WINDOW_HEIGHT*.6);
	playButton.setDimension(WINDOW_WIDTH / 3, 60);

}

void Menu::play( )
{
	timer = 6.f;
}

void Menu::draw()
{
	sfw::setBackgroundColor(WHITE);
	
	char play[64], exit[64];
	sprintf_s(play, "Play");
	sprintf_s(exit, "Exit");

	char buffer[64];
	sprintf_s(buffer, "SOLIPONGOUT");
	sfw::drawString(font, buffer, 55, WINDOW_HEIGHT*.9,	64, 64, 0, 0, BLACK);
	sfw::drawString(font, buffer, 45, WINDOW_HEIGHT*.9+10, 64, 64, 0, 0, WHITE);

	DrawButton(playButton, WINDOW_WIDTH*.35, WINDOW_HEIGHT*.6, WINDOW_WIDTH/3, 60, play, NONE, WHITE);
	DrawButton(exitButton, WINDOW_WIDTH*.35, WINDOW_HEIGHT*.3, WINDOW_WIDTH/3, 60, exit, NONE, WHITE);

	printf("mouseX: %f mouseY: %f \n", sfw::getMouseX(), sfw::getMouseY());
	printf("x1: %f y1: %f x2: %f y2: %f\n", playButton.getPosition().x, playButton.getPosition().y,
		playButton.getPosition().x + playButton.getDimension().x, playButton.getDimension().y);

	sfw::drawTexture(xhair, sfw::getMouseX(), sfw::getMouseY(), sfw::getTextureWidth(xhair) / 6, sfw::getTextureHeight(xhair) / 6, 45, true, 0, 0x88ffffaf);
}

void Menu::step()
{
	//if (playButton.isBoxColliding(sfw::getMouseX(), sfw::getMouseY()) {};
}

void Menu::DrawButton(Box b, float x, float y, int width, int height, char text[], int color, int fill) const
{
	Box temp;
	temp.setPosition(x, y);
	temp.setDimension(width, height);
	temp.DrawBox(color, fill);
	sfw::drawString(font, text, x, y+(height/2), width/4, height/3, 0, 0, BLACK);
}

APP_STATE Menu::next()
{
	if ( sfw::getKey('1') || (playButton.isBoxColliding(sfw::getMouseX(), sfw::getMouseY()) && sfw::getMouseButton(0)))
		return ENTER_GAME;
	return MENU;
}
