// Zomawia Sailo
// <zomawia@gmail.com>
// SoliPong

//The basic rules of the game are as follows;
// The game space consists of 4 boundaries around a rectangular playing field.
// Player begins the game in the bottom - center of the screen in front of the boundary.
// The game begins with the ball moving from the center of the field to the player's paddle.
// Whenever the ball collides with the player's paddle, the player's score should increase and the ball should bounce back.
//	The score should also be visible on the screen.
// Whenever the ball collides with the boundary opposite of the player's paddle,
//	it should bounce back in a pseudo-random direction.
// The side boundaries should only reverse the X direction the ball is travelling.
// The speed of the ball, in addition to other factors, should be partially dependent upon the player's score.
// The game ends when the ball passes the player's boundary as they fail to bounce it back.

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include "Splash.h"
#include "Gamestate.h"
#include "constded.h"
#include "Menu.h"
#include "Gameover.h"

// Random number generator
float randomRange(int start, int end)
{	
	return (rand() % (end - start + 1) + start);
}

void main()
{
	srand(time(0)); // seeding
	sfw::initContext(WINDOW_WIDTH,WINDOW_HEIGHT,"Solipongbreakout");
		
	Splash sploosh;
	Menu mush;
	Gameover gish;

	bool quit = false;
	
	APP_STATE state = ENTER_SPLASH;
	
	GameState gs;
	
	sploosh.init(gs.d);
	mush.init(gs.d, gs.u);
	gish.init(gs.f);
	

	while (sfw::stepContext() && !quit)
	{				
		switch (state)
		{
		case ENTER_SPLASH:
			sploosh.play();
		case SPLASH:
			sploosh.step();
			sploosh.draw();
			state = sploosh.next();
			break;

		case ENTER_MENU:
			mush.play();
		case MENU:
			mush.step();
			mush.draw();
			state = mush.next();
			break;

		case ENTER_GAME:
			gs.CreateGameState();
		case GAME:
			gs.UpdateGameState();
			gs.DrawGameState();
			state = gs.next();
			break;

		case ENTER_GAMEOVER:
			gish.play();
		case GAMEOVER:
			gs.UpdateGameState();
			gish.step();
			gs.DrawGameState();
			gish.draw();
			state = gish.next();
			break;

		case EXIT: quit = true;
			

			
		}
	}

	sfw::termContext();
}