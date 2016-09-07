// Zomawia Sailo
// <zomawia@gmail.com>

#include <cstdio>
#include <cstdlib>
#include "sfwdraw.h"
#include "solipong.h"
#include <time.h>

float randomRange(int start, int end)
{
	
	return (rand() % (end - start + 1) + start);

}

void DrawRectangle(Line top, Line bottom, Line left, Line right, unsigned tint = 0xffffffff)
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
	sfw::initContext(WINDOW_WIDTH,WINDOW_HEIGHT,"Solipong");

	//unsigned f = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);
	//unsigned d = sfw::loadTextureMap("./res/fontmap.png",16,16);
	unsigned r = sfw::loadTextureMap("./res/background.jpg");
	//unsigned u = sfw::loadTextureMap("./res/crosshair.png");

	Boundary myBoundary = {};
	Ball myBall[5] = {};
	BigPaddle myBigPaddle =
	{
		PADDLE_X_POS, PADDLE_Y_POS, PADDLE_X_POS+100, PADDLE_Y_POS,			//TOP
		PADDLE_X_POS, PADDLE_Y_POS -10, PADDLE_X_POS +100, PADDLE_Y_POS -10,	//BOTTOM
		PADDLE_X_POS, PADDLE_Y_POS, PADDLE_X_POS, PADDLE_Y_POS -10,			//LEFT
		PADDLE_X_POS +100, PADDLE_Y_POS, PADDLE_X_POS +100, PADDLE_Y_POS -10	//RIGHT	
	};

	// create balls in array
	for (int i = 0; i < 5; ++i)
	{
		myBall[i] = createBall(WINDOW_WIDTH/2+i*6, WINDOW_HEIGHT/2+i*12, 0, -7.5, i * 2 + 8);
	}

	sfw::setBackgroundColor(WHITE);

	while (sfw::stepContext())
	{		

		// Draw Paddle
		//sfw::drawLine(myPaddle.top.xMin, myPaddle.top.yMin, myPaddle.top.xMax, myPaddle.top.yMax, BLACK);

		//Draw Boundary
		sfw::drawLine(myBoundary.BotLeft.x+1, myBoundary.BotLeft.y+1, myBoundary.TopLeft.x+1, myBoundary.TopLeft.y-1, GREEN);
		sfw::drawLine(myBoundary.TopLeft.x + 1, myBoundary.TopLeft.y - 1, myBoundary.TopRight.x - 1, myBoundary.TopRight.y - 1, GREEN);
		sfw::drawLine(myBoundary.TopRight.x - 1, myBoundary.TopRight.y - 1, myBoundary.BottomRight.x - 1, myBoundary.BottomRight.y + 1, GREEN);
		sfw::drawLine(myBoundary.BotLeft.x + 1, myBoundary.BotLeft.y + 1, myBoundary.BottomRight.x - 1, myBoundary.BottomRight.y + 1, GREEN);

		// Update paddle X & Y axis by mouse location
		//myPaddle.top.xMin = sfw::getMouseX();
		//myPaddle.top.xMax = sfw::getMouseX() + 100;
		//myPaddle.top.yMin = PADDLE_Y_POS;
		//myPaddle.top.yMax = PADDLE_Y_POS;
		
		//myBall.velocity.x += sfw::getDeltaTime();
		//myBall.velocity.y += sfw::getDeltaTime();

		// Draw BigPaddle (RECTANGLE)
		DrawRectangle(myBigPaddle.Top, myBigPaddle.Bottom, myBigPaddle.Left, myBigPaddle.Right, RED);

		// Update BigPaddle
		UpdateRectangle(myBigPaddle);
		
		for (int i = 0; i < 5; ++i)
		{
			// Draw Ball
			sfw::drawCircle(myBall[i].position.x, myBall[i].position.y, myBall[i].radius, 16, MAGENTA);
			
			//Update ball location
			myBall[i].position.x += myBall[i].velocity.x;
			myBall[i].position.y += myBall[i].velocity.y;

			//Ball bounding for boundaries
			if (myBall[i].position.y > WINDOW_HEIGHT) // TOP
			{
				
				myBall[i].velocity.x += randomRange(-2, 2);
				myBall[i].velocity.y *= -1;
				
			}
			if (myBall[i].position.x > WINDOW_WIDTH)		myBall[i].velocity.x *= -1;	// RIGHT
			if (myBall[i].position.x < 0)					myBall[i].velocity.x *= -1;	// LEFT

			//Ball collision for paddle
			if ( (myBall[i].position.y <= PADDLE_Y_POS) && (myBall[i].position.x >= myBigPaddle.Top.xMin && myBall[i].position.x <= myBigPaddle.Top.xMax))
			{
				myBall[i].position.y = PADDLE_Y_POS;
				myBall[i].velocity.x *= 1;
				myBall[i].velocity.y *= -1;
			}
		}
		
		// Paddle bounding for boundaries
		
		//if (myPaddle.top.xMin < 0)
		//{
		//	myPaddle.top.xMin = 5;
		//	myPaddle.top.xMax = myPaddle.top.xMin + 100;
		//}
		//if (myPaddle.top.xMax > WINDOW_WIDTH)
		//{
		//	myPaddle.top.xMax = WINDOW_WIDTH - 5;
		//	myPaddle.top.xMin = myPaddle.top.xMax - 100;
		//}
		//if (myPaddle.top.yMin > WINDOW_HEIGHT / 6 || myPaddle.top.yMax > WINDOW_HEIGHT / 3)
		//{
		//	myPaddle.top.yMin = WINDOW_HEIGHT / 6;
		//	myPaddle.top.yMax = WINDOW_HEIGHT / 6;
		//}

		//if (myPaddle.top.yMin < 0 || myPaddle.top.yMax < 0)
		//{
		//	myPaddle.top.yMin = 5;
		//	myPaddle.top.yMax = 5;
		//}


		

		//printf("VEL:(%f,%f) Y-POS: (%f)\n", myBall.velocity.x, myBall.velocity.y, myBall.position.y);

		//sfw::drawString(f, " !\"#$%&'()*+,./-\n0123456789:;<=>?\n@ABCDEFGHIJKLMNO\nPQRSTUVWXYZ[\\]^_\n`abcdefghijklmno\npqrstuvwxyz{|}~", 0, 600, 48, 48, 0, ' ');
		sfw::drawTexture(r, 0, 600, 800, 600, 0, false,0, 0x8888880F);
		
		//sfw::drawString(d, "TIME 4 FUN", 400, 300, 48, 48, -acc*24,'\0',MAGENTA);

		//sfw::drawString(d, "6", 400, 32, 24, 24);
		//sfw::drawString(d, "12", 400, 600 - 32, 24, 24);
		//sfw::drawString(d, "3", 800-32, 300, 24, 24);
		//sfw::drawString(d, "9", 32, 300, 24, 24);

		//if (sfw::getMouseButton(MOUSE_BUTTON_RIGHT))
		//{
		//	sfw::drawTexture(u, sfw::getMouseX(), sfw::getMouseY(), sfw::getTextureWidth(u) / 2.5, sfw::getTextureHeight(u) / 2.5, 45, true, 0, 0x88ffffff);
		//	acc += 100;
		//}
		//else sfw::drawTexture(u, sfw::getMouseX(), sfw::getMouseY(), sfw::getTextureWidth(u)/2, sfw::getTextureHeight(u)/2);
	}

	sfw::termContext();
}