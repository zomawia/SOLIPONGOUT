// Zomawia Sailo
// <zomawia@gmail.com>
// SoliPong. It's like Breakout but not as fun.

#include <cstdio>
#include <cstdlib>
#include "Gamestate.h"
#include <time.h>
#include "solipong.h"

// Random number generator
float randomRange(int start, int end)
{	
	return (rand() % (end - start + 1) + start);
}

void main()
{
	srand(time(0)); // seeding
	sfw::initContext(WINDOW_WIDTH,WINDOW_HEIGHT,"Solipongbreakout");

	GameState gs = gs.CreateGameState();	

	// main game loop
	while (sfw::stepContext())
	{				
		gs.UpdateGameState(gs);
		gs.DrawGameState(gs);	
	}

	sfw::termContext();
}