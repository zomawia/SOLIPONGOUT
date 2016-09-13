#pragma once

#include "solipong.h"

class GameState
{
private:
	bool bisGameOver = false;
	int BallsLeft = 5;
	int totalPoints = 0;

	Ball myBall[5] = {};
	int myBallArraySize = 5;
	Box myBox = {};
	Box myBorder = {};
	
	unsigned f = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	unsigned d = sfw::loadTextureMap("./res/fontmap.png", 16, 16);
	unsigned r = sfw::loadTextureMap("./res/background.jpg");

public:
	//create gamestate
	GameState CreateGameState();

	//update function
	void UpdateGameState(GameState &gs);

	//draw function
	void DrawGameState(GameState &gs);
};