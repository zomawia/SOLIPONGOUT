// Zomawia Sailo
// <zomawia@gmail.com>

#include <cstdio>
#include <cstdlib>
#include "sfwdraw.h"
#include "Gamestate.h"
#include <time.h>
#include <string> 

// Random number generator
float randomRange(int start, int end)
{	
	return (rand() % (end - start + 1) + start);
}

Box CreateBox()
{
	Box b;
	b.x = PADDLE_X_POS;
	b.y = PADDLE_Y_POS;
	b.width = WINDOW_WIDTH/4;
	b.height = paddleHeight;

	return b;
}

// starts drawing from the bottom left corner
void DrawBox(float x, float y, int width, int height, unsigned color, unsigned fill)
{	
	sfw::drawLine(x, y, x + width, y, color);					// BOTTOM
	sfw::drawLine(x, y, x , y + height, color);					// LEFT
	sfw::drawLine(x, y + height, x + width, y + height, color); // TOP
	sfw::drawLine(x + width, y, x + width, y + height, color);	// RIGHT

	//FILL
	for (int i = height; i > 1; --i)
	{
		sfw::drawLine(x, y + i-1, x + width - 1, y + i-1, fill);
	}
}

void UpdateBox(Box &b)
{
	b.x = sfw::getMouseX();
	//b.y = sfw::getMouseY();
}

void DrawRectangle(Line top, Line bottom, Line left, Line right, unsigned tint)
{
	sfw::drawLine(top.xMin, top.yMin, top.xMax, top.yMax, tint); //TOP
	sfw::drawLine(bottom.xMin, bottom.yMin, bottom.xMax, bottom.yMax, tint); //BOTTOM
	sfw::drawLine(left.xMin, left.yMin, left.xMax, left.yMax, tint); //LEFT
	sfw::drawLine(right.xMin, right.yMin, right.xMax, right.yMax, tint); //RIGHT
}

void UpdateRectangle(BigPaddle &b)
{
	//Update BigPaddle
	b.Top.xMin = sfw::getMouseX();
	b.Top.xMax = sfw::getMouseX() + paddleLength;
	b.Bottom.xMin = sfw::getMouseX();
	b.Bottom.xMax = sfw::getMouseX() + paddleLength;
	b.Left.xMin = sfw::getMouseX();
	b.Left.xMax = sfw::getMouseX();
	b.Right.xMin = sfw::getMouseX() + paddleLength;
	b.Right.xMax = sfw::getMouseX() + paddleLength;
}

Ball createBall(float posX, float posY, float veloX,float veloY, float radius)
{
	Ball temp;

	temp.position.x = posX;
	temp.position.y = posY;
	temp.velocity.x = veloX;
	temp.velocity.y = veloY;
	temp.radius = radius;

	return temp;
}

GameState CreateGameState()
{
	GameState temp;
	
	temp.myBigPaddle = {
		PADDLE_X_POS, PADDLE_Y_POS, PADDLE_X_POS + 200, PADDLE_Y_POS,				//TOP
			PADDLE_X_POS, PADDLE_Y_POS - 10, PADDLE_X_POS + 200, PADDLE_Y_POS - 10,	//BOTTOM
			PADDLE_X_POS, PADDLE_Y_POS, PADDLE_X_POS, PADDLE_Y_POS - 10,			//LEFT
			PADDLE_X_POS + 200, PADDLE_Y_POS, PADDLE_X_POS + 200, PADDLE_Y_POS - 10	//RIGHT	
	};

	// create balls in array with function
	for (int i = 0; i < 5; ++i)
	{
		temp.myBall[i] = createBall(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, randomRange(-3, -1), randomRange(8, 24));
	}

	temp.myBox = CreateBox();
	
	return temp;
}

void UpdateGameState(GameState &gs) //collision checking and variable updates?
{
	// Update BigPaddle, stop updating if game over
	if (!bisGameOver) UpdateRectangle(gs.myBigPaddle);
	else sfw::drawString(gs.f, "GAME OVER", 180, WINDOW_HEIGHT - 55, 50, 50, 0, ' ', 0xbfbfbfff);

	// Collision stuff
	for (int i = 0; i < 5; ++i)
	{
		//Update ball location
		gs.myBall[i].position.x += gs.myBall[i].velocity.x;
		gs.myBall[i].position.y += gs.myBall[i].velocity.y;

		//Ball collision for boundaries
		if (gs.myBall[i].position.y + gs.myBall[i].radius >= WINDOW_HEIGHT) // TOP
		{
			totalPoints++;
			gs.myBall[i].velocityMult += .05f;
			gs.myBall[i].velocity.x += randomRange(-3, 3);
			gs.myBall[i].velocity.y *= -(1 + gs.myBall[i].velocityMult);
		}
		if (gs.myBall[i].position.x + gs.myBall[i].radius >= WINDOW_WIDTH)		gs.myBall[i].velocity.x *= -1;	// RIGHT
		if (gs.myBall[i].position.x - gs.myBall[i].radius <= 0)					gs.myBall[i].velocity.x *= -1;	// LEFT


		//Ball collision for paddle			
		if (gs.myBall[i].position.y - gs.myBall[i].radius <= PADDLE_Y_POS)
			if (gs.myBall[i].outBounds == false)
			{
				if (gs.myBall[i].position.x >= gs.myBigPaddle.Top.xMin && gs.myBall[i].position.x <= gs.myBigPaddle.Top.xMax)
				{
					gs.myBall[i].velocity.x *= 1;
					gs.myBall[i].velocity.y *= -1;
				}

				else if (gs.myBall[i].position.y < PADDLE_Y_POS - 8 && gs.myBall[i].bBallDestroyed == false)
				{
					gs.myBall[i].outBounds = true;
					gs.myBall[i].bBallDestroyed = true;
					BallsLeft--;
				}

			}

	}

	if (BallsLeft <= 0)
	{
		bisGameOver = true;
	}

	UpdateBox(gs.myBox);

}

void DrawGameState(GameState &gs)
{
	for (int i = 0; i < 5; ++i)
	{
		// Draw Ball
		sfw::drawCircle(gs.myBall[i].position.x, gs.myBall[i].position.y, gs.myBall[i].radius, 16, BLACK);
	}

	// Draw Background
	sfw::setBackgroundColor(WHITE);
	sfw::drawTexture(gs.r, 0, 600, 800, 600, 0, false, 0, 0x8888880F);

	// Draw Score
	if (totalPoints < 10) sfw::drawString(gs.f, std::to_string(totalPoints).c_str(), WINDOW_WIDTH / 2 - 140, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);
	else sfw::drawString(gs.f, std::to_string(totalPoints).c_str(), WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);

	sfw::drawString(gs.f, "Balls:", 5, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfaf);
	sfw::drawString(gs.f, std::to_string(BallsLeft).c_str(), 158, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfff);

	//Draw Boundary Lines
	sfw::drawLine(gs.myBoundary.BotLeft.x + 1, gs.myBoundary.BotLeft.y + 1, gs.myBoundary.TopLeft.x + 1, gs.myBoundary.TopLeft.y - 1, GREEN);
	sfw::drawLine(gs.myBoundary.TopLeft.x + 1, gs.myBoundary.TopLeft.y - 1, gs.myBoundary.TopRight.x - 1, gs.myBoundary.TopRight.y - 1, GREEN);
	sfw::drawLine(gs.myBoundary.TopLeft.x + 1, gs.myBoundary.TopLeft.y - 2, gs.myBoundary.TopRight.x - 1, gs.myBoundary.TopRight.y - 2, GREEN);
	sfw::drawLine(gs.myBoundary.TopRight.x - 1, gs.myBoundary.TopRight.y - 1, gs.myBoundary.BottomRight.x - 1, gs.myBoundary.BottomRight.y + 1, GREEN);
	//sfw::drawLine(myBoundary.BotLeft.x + 1, myBoundary.BotLeft.y + 1, myBoundary.BottomRight.x - 1, myBoundary.BottomRight.y + 1, GREEN);

	// Draw BigPaddle using function
	DrawRectangle(gs.myBigPaddle.Top, gs.myBigPaddle.Bottom, gs.myBigPaddle.Left, gs.myBigPaddle.Right, RED);

	DrawBox(gs.myBox.x, gs.myBox.y, gs.myBox.width, gs.myBox.height);
}


void main()
{
	srand(time(0)); // seeding
	sfw::initContext(WINDOW_WIDTH,WINDOW_HEIGHT,"Solipongbreakout");

	GameState gs = CreateGameState();	

	// main game loop
	while (sfw::stepContext())
	{		
		
		UpdateGameState(gs);
		DrawGameState(gs);
		

		
		
		//printf("VEL:(%f,%f) Y-POS: (%f)\n", myBall.velocity.x, myBall.velocity.y, myBall.position.y);
				
		//sfw::drawString(d, "TIME 4 FUN", 400, 300, 48, 48, -acc*24,'\0',MAGENTA);

		//if (sfw::getMouseButton(MOUSE_BUTTON_RIGHT))
		//{
		//	sfw::drawTexture(u, sfw::getMouseX(), sfw::getMouseY(), sfw::getTextureWidth(u) / 2.5, sfw::getTextureHeight(u) / 2.5, 45, true, 0, 0x88ffffff);
		//	acc += 100;
		//}
		//else sfw::drawTexture(u, sfw::getMouseX(), sfw::getMouseY(), sfw::getTextureWidth(u)/2, sfw::getTextureHeight(u)/2);
	}

	sfw::termContext();
}