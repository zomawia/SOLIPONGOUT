#include "Splash.h"
#include <cstdio>
#include "sfwdraw.h"

void Splash::init(int a_font){ font = a_font;}

void Splash::play() { timer = 6.f; }

void Splash::draw()
{
	char press[64];
	char buffer[64];
	sprintf_s(press, "Press ENTER or click mouse");	
	sprintf_s(buffer, "SOLIPONGOUT");

	sfw::drawString(font, buffer, 60, 350, 64 * (timer / 6.f), 64 * (timer / 6.f), 0, 0, BLACK);
	sfw::drawString(font, buffer, 50, 360, 64 * (timer / 6.f), 64 * (timer / 6.f), 0, 0, WHITE);

	sfw::drawString(font, press, 66, 58, 24, 24, 0, 0, BLACK);
	sfw::drawString(font, press, 64, 60, 24, 24, 0, 0, RED);

}

void Splash::step() { timer -= sfw::getDeltaTime(); }

APP_STATE Splash::next()
{
	if (sfw::getKey(KEY_ENTER) || sfw::getMouseButton(0))
		return ENTER_MENU;

	if (sfw::getKey('5'))
		return ENTER_GAMEOVER;

	if (timer <= 0)
	{
		timer = 6.f;
	}
	
	return SPLASH;
}
