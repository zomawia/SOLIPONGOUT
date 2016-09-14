#include "Gameover.h"
#include "sfwdraw.h"

void Gameover::init(int a_font)
{
	font = a_font;
}

void Gameover::play()
{
}

void Gameover::draw()
{
	sfw::drawString(font, "GAME OVER", 180, WINDOW_HEIGHT - 55, 50, 50, 0, ' ', 0xbfbfbfff);

	sfw::drawString(font, "Press SPACEBAR to play again",	25, 125, 25, 25, 0, ' ', 0xbfbfbfff);

	sfw::drawString(font, "ESC to go back to menu.",					25, 100, 25, 25, 0, ' ', 0xbfbfbfff);
}

void Gameover::step()
{
}

APP_STATE Gameover::next()
{
	if (sfw::getKey(KEY_ESCAPE)) return ENTER_MENU;
	if (sfw::getKey(' ') || sfw::getMouseButton(0)) return ENTER_GAME;
	return GAMEOVER;
}
