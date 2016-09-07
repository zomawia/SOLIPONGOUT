// Zomawia Sailo
// <zomawia@gmail.com>

#include <cstdio>
#include <cstdlib>
#include "sfwdraw.h"
#include "solipong.h"
#include <time.h>
#include <string> 

// Random number generator
float randomRange(int start, int end)
{	
	return (rand() % (end - start + 1) + start);
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
	b.Top.xMax = sfw::getMouseX() + 100;
	b.Bottom.xMin = sfw::getMouseX();
	b.Bottom.xMax = sfw::getMouseX() + 100;
	b.Left.xMin = sfw::getMouseX();
	b.Left.xMax = sfw::getMouseX();
	b.Right.xMin = sfw::getMouseX() + 100;
	b.Right.xMax = sfw::getMouseX() + 100;
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

void main()
{
	srand(time(0)); // seeding
	sfw::initContext(WINDOW_WIDTH,WINDOW_HEIGHT,"Solipongbreakout");

	unsigned f = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	unsigned d = sfw::loadTextureMap("./res/fontmap.png",16,16);
	unsigned r = sfw::loadTextureMap("./res/background.jpg");
	//unsigned u = sfw::loadTextureMap("./res/crosshair.png");

	Boundary myBoundary = {};
	Ball myBall[5] = {};
	BigPaddle myBigPaddle =
	{
		PADDLE_X_POS, PADDLE_Y_POS, PADDLE_X_POS+200, PADDLE_Y_POS,			//TOP
		PADDLE_X_POS, PADDLE_Y_POS -10, PADDLE_X_POS +200, PADDLE_Y_POS -10,	//BOTTOM
		PADDLE_X_POS, PADDLE_Y_POS, PADDLE_X_POS, PADDLE_Y_POS -10,			//LEFT
		PADDLE_X_POS +200, PADDLE_Y_POS, PADDLE_X_POS +200, PADDLE_Y_POS -10	//RIGHT	
	};

	// create balls in array with function
	for (int i = 0; i < 5; ++i)
	{
		myBall[i] = createBall(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0, randomRange(-5, -1), randomRange(8,24));
	}	

	

	// main game loop
	while (sfw::stepContext())
	{		

		// Draw Background
		sfw::setBackgroundColor(WHITE);
		sfw::drawTexture(r, 0, 600, 800, 600, 0, false, 0, 0x8888880F);

		// Draw Score
		if (totalPoints < 10) sfw::drawString(f, std::to_string(totalPoints).c_str(), WINDOW_WIDTH/2-150, WINDOW_HEIGHT/2+150, 300, 300, 0, ' ', 0xbfbfbf11);
		else sfw::drawString(f, std::to_string(totalPoints).c_str(), WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf11);
		//sfw::drawString(f, "0", WINDOW_WIDTH/2-150, WINDOW_HEIGHT/2+150, 300, 300, 0, ' ', 0xbfbfbf2f);
		
		//Draw Boundary Lines
		sfw::drawLine(myBoundary.BotLeft.x+1, myBoundary.BotLeft.y+1, myBoundary.TopLeft.x+1, myBoundary.TopLeft.y-1, GREEN);
		sfw::drawLine(myBoundary.TopLeft.x + 1, myBoundary.TopLeft.y - 1, myBoundary.TopRight.x - 1, myBoundary.TopRight.y - 1, GREEN);
		sfw::drawLine(myBoundary.TopLeft.x + 1, myBoundary.TopLeft.y - 2, myBoundary.TopRight.x - 1, myBoundary.TopRight.y - 2, GREEN);
		sfw::drawLine(myBoundary.TopRight.x - 1, myBoundary.TopRight.y - 1, myBoundary.BottomRight.x - 1, myBoundary.BottomRight.y + 1, GREEN);
		//sfw::drawLine(myBoundary.BotLeft.x + 1, myBoundary.BotLeft.y + 1, myBoundary.BottomRight.x - 1, myBoundary.BottomRight.y + 1, GREEN);
		
		//myBall.velocity.x += sfw::getDeltaTime();
		//myBall.velocity.y += sfw::getDeltaTime();

		// Draw BigPaddle using function
		DrawRectangle(myBigPaddle.Top, myBigPaddle.Bottom, myBigPaddle.Left, myBigPaddle.Right, RED);

		// Update BigPaddle
		UpdateRectangle(myBigPaddle);
		
		for (int i = 0; i < 5; ++i)
		{
			// Draw Ball
			sfw::drawCircle(myBall[i].position.x, myBall[i].position.y, myBall[i].radius, 16, BLACK);
			
			//Update ball location
			myBall[i].position.x += myBall[i].velocity.x;
			myBall[i].position.y += myBall[i].velocity.y;

			//Ball collision for boundaries
			if (myBall[i].position.y + myBall[i].radius >= WINDOW_HEIGHT) // TOP
			{	
				totalPoints++;
				myBall[i].velocity.x += randomRange(-3, 3);
				myBall[i].velocity.y *= -1 * (totalPoints*VELOCITY_MULT);				
			}
			if (myBall[i].position.x + myBall[i].radius >= WINDOW_WIDTH)		myBall[i].velocity.x *= -1;	// RIGHT
			if (myBall[i].position.x - myBall[i].radius <= 0)					myBall[i].velocity.x *= -1;	// LEFT

			//Ball collision for paddle			
			if (myBall[i].outBounds==false && (myBall[i].position.y - myBall[i].radius <= PADDLE_Y_POS) && (myBall[i].position.x >= myBigPaddle.Top.xMin && myBall[i].position.x <= myBigPaddle.Top.xMax))
			{
				myBall[i].velocity.x *= 1;
				myBall[i].velocity.y *= -1;				
			}

			if (myBall[i].position.y < PADDLE_Y_POS - 20) myBall[i].outBounds = true;
		}
		
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