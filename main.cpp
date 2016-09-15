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
	sfw::initContext(WINDOW_WIDTH,WINDOW_HEIGHT,"Solipongout");
		
	Splash intro;
	Menu mainMenu;
	Gameover gameOver;
	GameState gs;

	bool quit = false;
	
	APP_STATE state = ENTER_SPLASH;	
	
	intro.init(gs.block_font);
	mainMenu.init(gs.block_font, gs.mousecursor);
	gameOver.init(gs.tonc_font);
	

	while (sfw::stepContext() && !quit)
	{				
		switch (state)
		{
		case ENTER_SPLASH:
			intro.play();
		case SPLASH:
			intro.step();
			intro.draw();
			state = intro.next();
			break;

		case ENTER_MENU:
			mainMenu.play();
		case MENU:
			mainMenu.step();
			mainMenu.draw();
			state = mainMenu.next();
			break;

		case ENTER_GAME:
			gs.CreateGameState();
		case GAME:
			gs.UpdateGameState();
			gs.DrawGameState();
			state = gs.next();
			break;

		case ENTER_GAMEOVER:
			gameOver.play();
		case GAMEOVER:
			gs.UpdateGameState();
			gameOver.step();
			gs.DrawGameState();
			gameOver.draw();
			state = gameOver.next();
			break;

		case EXIT: quit = true;			
		}
	}

	sfw::termContext();
}