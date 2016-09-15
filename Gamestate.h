#pragma once

#include "solipong.h"
#include "constded.h"

class GameState
{
private:
	bool bisGameOver;
	int BallsLeft;
	int totalPoints;

	Ball myBall[5];
	int myBallArraySize = 5;
	Box myPaddle;
	Box myBorder;

public:

	unsigned tonc_font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	unsigned block_font = sfw::loadTextureMap("./res/fontmap.png", 16, 16);
	unsigned background = sfw::loadTextureMap("./res/background.jpg");
	unsigned mousecursor = sfw::loadTextureMap("./res/crosshair.png");

	//create gamestate
	void CreateGameState();

	//update function
	void UpdateGameState();

	//draw function
	void DrawGameState();

	APP_STATE next();
};