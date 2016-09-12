#pragma once

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_Y_POS = WINDOW_HEIGHT / 8;
const float PADDLE_X_POS = WINDOW_WIDTH / 2 - 50;
const int paddleLength = 200;
const int paddleHeight = 12;
const float matrix[16] = { 1,0,0,0,  0,1,0,0, 0,0,1,0, 0,0,0,1 };
bool bisGameOver = false;
int BallsLeft = 5;

int totalPoints = 0;

//struct Line
//{
//	float xMin, yMin, xMax, yMax;
//};
//

//struct Paddle
//{
//	Line top;
//};
//
//struct BigPaddle
//{
//	Line Top, Bottom, Left, Right;
//};

struct vector2d
{
	float x, y;
};

struct Box
{
	float x, y;
	int width, height;
};

//struct Boundary
//{
//	Point BotLeft = { 0, 0 };
//	Point TopLeft = { 0, WINDOW_HEIGHT };
//	Point TopRight = { WINDOW_WIDTH, WINDOW_HEIGHT };
//	Point BottomRight = { WINDOW_WIDTH, 0 };
//};

struct Ball
{
	vector2d position, velocity;
	float radius;
	bool outBounds = false;
	//bool bBallDestroyed = false;
	float velocityMult = 1.0f;

};

//void DrawRectangle(Line top, Line bottom, Line left, Line right, unsigned tint = 0xffffffff);
//
//void UpdateRectangle(BigPaddle &b);

Ball createBall(float posX, float posY, float veloX, float veloY, float radius);

float randomRange(int start, int end);

Box CreateBox(Box &b);

void DrawBox(float x, float y, int width = 200, int height = 15, unsigned color = BLACK, unsigned fill = MAGENTA);

void UpdateBox(Box &b);