#include "Menu.h"
#include <cstdio>

void Menu::init(int a_font, int a_xhair)
{ 
	font = a_font; 
	xhair = a_xhair;
	isPlaySelected = true;
}

void Menu::play( )
{
	timer = 6.f;
}

void Menu::draw()
{
	sfw::setBackgroundColor(WHITE);
	
	char play[64], exit[64], credits[64];
	sprintf_s(play, "Play");
	sprintf_s(exit, "Exit");
	sprintf_s(credits, "About");

	char buffer[64];
	sprintf_s(buffer, "SOLIPONGOUT");
	sfw::drawString(font, buffer, 55, WINDOW_HEIGHT*.9,	64 * (timer / 6.f), 64 * (timer / 6.f), 0, 0, BLACK);
	sfw::drawString(font, buffer, 45, WINDOW_HEIGHT*.9+10, 64 * (timer / 6.f), 64 * (timer / 6.f), 0, 0, WHITE);

	if (bisSoliActivate == true)
	{
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 50), randomRange(14, 60), randomRange(0, 360), 0, BLACK);
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 60), randomRange(0, 360), 0, RED);
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 50), randomRange(14, 60), randomRange(0, 360), 0, BLACK);
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 60), randomRange(0, 360), 0, RED);
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 50), randomRange(14, 60), randomRange(0, 360), 0, BLACK);
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 60), randomRange(0, 360), 0, RED);
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 50), randomRange(14, 60), randomRange(0, 360), 0, BLACK);
		sfw::drawString(font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 60), randomRange(0, 360), 0, RED);
	}
	
	if (playButton.isBoxColliding(sfw::getMouseX(), sfw::getMouseY()))
	{
		DrawButton(playButton, WINDOW_WIDTH*.37, WINDOW_HEIGHT*.5, WINDOW_WIDTH / 4, 80, play, BLACK, NONE);
	}
	else 
	{
		DrawButton(playButton, WINDOW_WIDTH*.37, WINDOW_HEIGHT*.5, WINDOW_WIDTH / 4, 80, play, NONE, NONE);
	}
	
	if (exitButton.isBoxColliding(sfw::getMouseX(), sfw::getMouseY()))
	{
		DrawButton(exitButton, WINDOW_WIDTH*.37, WINDOW_HEIGHT*.3, WINDOW_WIDTH / 4, 80, exit, BLACK, NONE);
	}
	else
	{
		DrawButton(exitButton, WINDOW_WIDTH*.37, WINDOW_HEIGHT*.3, WINDOW_WIDTH / 4, 80, exit, NONE, NONE);
	}

	DrawButton(creditsButton, WINDOW_WIDTH*.7, WINDOW_HEIGHT*.1, WINDOW_WIDTH / 6, 40, credits, NONE, NONE);

	//printf("mouseX: %f mouseY: %f \n", sfw::getMouseX(), sfw::getMouseY());
	//printf("x1: %f y1: %f x2: %f y2: %f\n", playButton.getPosition().x, playButton.getPosition().y,
	//	playButton.getPosition().x + playButton.getDimension().x, playButton.getDimension().y);

	sfw::drawTexture(xhair, sfw::getMouseX(), sfw::getMouseY(), sfw::getTextureWidth(xhair) / 6, sfw::getTextureHeight(xhair) / 6, 0, true, 0, 0x88ffffaf);
}

void Menu::step()
{
	timer -= sfw::getDeltaTime();

	playButton.setPosition(WINDOW_WIDTH*.37, WINDOW_HEIGHT*.5);
	playButton.setDimension(WINDOW_WIDTH / 3, 60);

	exitButton.setPosition(WINDOW_WIDTH*.37, WINDOW_HEIGHT*.3);
	exitButton.setDimension(WINDOW_WIDTH / 3, 60);

	creditsButton.setPosition(WINDOW_WIDTH*.7, WINDOW_HEIGHT*.1);
	creditsButton.setDimension(WINDOW_WIDTH / 3, 60);

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
	if (timer <= 5.90f) timer = 6.f;
	
	if ( sfw::getKey('1') || (playButton.isBoxColliding(sfw::getMouseX(), sfw::getMouseY()) && sfw::getMouseButton(0)))
		return ENTER_GAME;

	if (sfw::getKey('3') || (creditsButton.isBoxColliding(sfw::getMouseX(), sfw::getMouseY()) && sfw::getMouseButton(0)))
		return ENTER_CREDITS;

	if (exitButton.isBoxColliding(sfw::getMouseX(), sfw::getMouseY()) && sfw::getMouseButton(0)) return EXIT;

	//if (sfw::getKey(KEY_ESCAPE)) return EXIT;

	return MENU;
}
