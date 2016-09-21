#include "Splash.h"
#include <cstdio>
#include "sfwdraw.h"

void Splash::init(int a_font) { font = a_font; }

void Splash::play() { timer = 6.f; mover = 4.f; xPos = 600; xSpot = 600;}

void Splash::draw()
{
	char press[64];
	char buffer[64];
	sprintf_s(press, "Press ENTER or click mouse");	
	sprintf_s(buffer, "SOLIPONGOUT");

	sfw::drawString(font, buffer, 60, 350, 64 * (timer / 6.f), 64 * (timer / 6.f), 0, 0, BLACK);
	sfw::drawString(font, buffer, 50, 360, 64 * (timer / 6.f), 64 * (timer / 6.f), 0, 0, WHITE);

	if (xSpot > 62)
	{
		sfw::drawString(font, press, xPos * (mover / 4.f),	58, 24, 24, 0, 0, BLACK);
		sfw::drawString(font, press, xPos * (mover / 4.f),	60, 24, 24, 0, 0, RED);
		xSpot = xPos *(mover / 4.f);
	}
	else
	{
		sfw::drawString(font, press, 64, 58, 24, 24, 0, 0, BLACK);
		sfw::drawString(font, press, 62, 60, 24, 24, 0, 0, RED);
	}
}

void Splash::step() { timer -= sfw::getDeltaTime(); mover -= sfw::getDeltaTime();}

APP_STATE Splash::next()
{
	if (sfw::getKey(KEY_ENTER) || sfw::getMouseButton(0))
		return ENTER_MENU;

	if (sfw::getKey('5'))
		return ENTER_GAME;

	if (timer <= 5.95)
	{
		timer = 6.f;
	}
	
	return SPLASH;
}
