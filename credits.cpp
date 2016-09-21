#include "credits.h"
#include <cstdio>
#include "sfwdraw.h"

void Credits::init(int a_font) { font = a_font; }

void Credits::play() { timer = 6.f; moverNum = 8.f; yPos = 80; yCount = 200; mover = moverNum; }

void Credits::draw()
{
	char p1[64], p2[64], p3[64], p4[64];
	char exit[64];
	sprintf_s(p1, "Programming");
	sprintf_s(p2, "Zomawia Sailo");
	sprintf_s(p3, "'Artwork'");
	sprintf_s(p4, "Press ESC to exit");

	sfw::drawString(font, p4, 10, WINDOW_HEIGHT-40, 32, 32, 0, 0, BLACK);

	if (yCount < WINDOW_HEIGHT-100)
	{
		sfw::drawString(font, p1, WINDOW_WIDTH * .3, yPos / (mover / moverNum), 24, 24, 0, 0, BLACK);
		sfw::drawString(font, p1, WINDOW_WIDTH * .3, yPos / (mover / moverNum)-2, 24, 24, 0, 0, RED);

		sfw::drawString(font, p2, WINDOW_WIDTH * .35, yPos / (mover / moverNum) -26, 24, 24, 0, 0, BLACK);
		sfw::drawString(font, p2, WINDOW_WIDTH * .35, yPos / (mover / moverNum) -24, 24, 24, 0, 0, RED);

		sfw::drawString(font, p3, WINDOW_WIDTH * .3, yPos / (mover / moverNum) -60, 24, 24, 0, 0, BLACK);
		sfw::drawString(font, p3, WINDOW_WIDTH * .3, yPos / (mover / moverNum) -58, 24, 24, 0, 0, RED);

		sfw::drawString(font, p2, WINDOW_WIDTH * .35, yPos / (mover / moverNum) -84, 24, 24, 0, 0, BLACK);
		sfw::drawString(font, p2, WINDOW_WIDTH * .35, yPos / (mover / moverNum) -82, 24, 24, 0, 0, RED);

		yCount = yPos / (mover / moverNum);
	}
	else
	{
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT), 
			randomRange(1, 50), randomRange(14, 410), randomRange(0, 360), 0, BLACK);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 140), randomRange(0, 360), 0, RED);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 45), randomRange(4, 440), randomRange(0, 360), 0, GREEN);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(14, 460), randomRange(4, 140), randomRange(0, 360), 0, BLUE);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(4, 420), randomRange(4, 40), randomRange(0, 360), 0, YELLOW);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(14, 46), randomRange(4, 14), randomRange(0, 360), 0, BLUE);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(4, 42), randomRange(4, 40), randomRange(0, 360), 0, YELLOW);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(14, 46), randomRange(4, 14), randomRange(0, 360), 0, BLUE);
		sfw::drawString(font, p2, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(4, 42), randomRange(4, 40), randomRange(0, 360), 0, YELLOW);
		bisSoliActivate = true;
	}
}

void Credits::step() { timer -= sfw::getDeltaTime(); mover -= sfw::getDeltaTime(); }

APP_STATE Credits::next()
{
	if (sfw::getKey(KEY_ESCAPE))
		return ENTER_MENU;

	if (timer <= 5.95)
	{
		timer = 6.f;
	}

	return CREDITS;
}
