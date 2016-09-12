#pragma once

#include "solipong.h"

struct GameState
{
	//Boundary myBoundary = {};
	Ball myBall[5] = {};
	int myBallArraySize = 5;
	//BigPaddle myBigPaddle = {};
	Box myBox = {};
	Box myBorder = {};
	
	unsigned f = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	unsigned d = sfw::loadTextureMap("./res/fontmap.png", 16, 16);
	unsigned r = sfw::loadTextureMap("./res/background.jpg");

};

//create gamestate
GameState CreateGameState();

//update function
void UpdateGameState(GameState &gs);

//draw function
void DrawGameState(GameState &gs);
