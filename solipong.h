#pragma once

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_Y_POS = WINDOW_HEIGHT / 8;
const float PADDLE_X_POS = WINDOW_WIDTH / 2 - 50;
const float matrix[16] = { 1,0,0,0,  0,1,0,0, 0,0,1,0, 0,0,0,1 };
const float VELOCITY_MULT = 1.00f;

char totalPoints = 0;

struct Line
{
	float xMin, yMin, xMax, yMax;
};

struct Point
{
	float x, y;
};
struct Paddle
{
	Line top;
};

struct BigPaddle
{
	Line Top, Bottom, Left, Right;
};

struct Boundary
{
	Point BotLeft = { 0, 0 };
	Point TopLeft = { 0, WINDOW_HEIGHT };
	Point TopRight = { WINDOW_WIDTH, WINDOW_HEIGHT };
	Point BottomRight = { WINDOW_WIDTH, 0 };
};

struct Ball
{
	Point position, velocity;
	float radius;
	
};
