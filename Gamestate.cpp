#include "Gamestate.h"
#include <string>


void GameState::CreateGameState()
{
	BallsLeft = 5;
	totalPoints = 0;
	myBall[5] = {};
	myBox = {};
	myBorder = {};
	bisGameOver = false;

	// create balls in array with function

	for (int i = 0; i < 5; ++i)
	{
		myBall[i] = myBall[i].createBall(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 
			randomRange(-3, -1), randomRange(8, 24));
	}

	myBox = myBox.CreateBox(PADDLE_X_POS, PADDLE_Y_POS, WINDOW_WIDTH / 4, 12);
	myBorder = myBox.CreateBox(1, 1, WINDOW_WIDTH - 2, WINDOW_HEIGHT - 2);

}

void GameState::UpdateGameState()
{
	// stop updating if game over
	if (!bisGameOver)
	{
		myBox.UpdateBox();
	}	

	// Collision stuff
	for (int i = 0; i < 5; ++i)
	{
		//Update ball location
		myBall[i].UpdateBall();

		//Ball collision for boundaries
		if (myBall[i].getPosition().y + myBall[i].getRadius() >= WINDOW_HEIGHT) // TOP
		{
			totalPoints++;
			//gs.myBall[i].setVelocityMult(.05f + gs.myBall[i].getVelocityMult);
			myBall[i].setVelocity(randomRange(-3, 3), -myBall[i].getVelocity().y);
			// +gs.myBall[i].getVelocityMult);
																						
			//gs.myBall[i].setVelocity.y *= -(1 + gs.myBall[i].getVelocityMult);
		}
		if (myBall[i].getPosition().x + myBall[i].getRadius() >= WINDOW_WIDTH)
			myBall[i].setVelocity(-myBall[i].getVelocity().x, myBall[i].getVelocity().y);	// RIGHT
		if (myBall[i].getPosition().x - myBall[i].getRadius() <= 0)
			myBall[i].setVelocity(-myBall[i].getVelocity().x, myBall[i].getVelocity().y);	// LEFT


		//Ball collision for paddle			
		if (myBall[i].getPosition().y - myBall[i].getRadius() <= PADDLE_Y_POS + myBox.getDimension().y
			&& !myBall[i].outBounds())
		{
			if (myBall[i].getPosition().x >= myBox.getPosition().x &&
				myBall[i].getPosition().x <= myBox.getPosition().x + myBox.getDimension().x)
			{
				myBall[i].setPosition(myBall[i].getPosition().x,
					myBall[i].getPosition().y + myBox.getDimension().y);
				myBall[i].setVelocity(myBall[i].getVelocity().x, -myBall[i].getVelocity().y);
			}

			else if (!myBall[i].outBounds() && !myBall[i].getOut() )
			{
				myBall[i].setOut();
				BallsLeft--;
			}
		}

	}

	if (BallsLeft <= 0)
	{
		bisGameOver = true;
	}
}

void GameState::DrawGameState()
{
	for (int i = 0; i < 5; ++i)
	{
		// Draw Ball
		sfw::drawCircle(myBall[i].getPosition().x, myBall[i].getPosition().y, myBall[i].getRadius(), 16, BLACK);
	}

	// Draw Background
	sfw::setBackgroundColor(WHITE);
	sfw::drawTexture(background, 0, 600, 800, 600, 0, false, 0, 0x8888880F);

	// Draw Score
	if (totalPoints < 10) sfw::drawString(tonc_font, std::to_string(totalPoints).c_str(), 
		WINDOW_WIDTH / 2 - 140, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);
	else sfw::drawString(tonc_font, std::to_string(totalPoints).c_str(), 
		WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);

	sfw::drawString(tonc_font, "BALLS:", 5, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfaf);
	sfw::drawString(tonc_font, std::to_string(BallsLeft).c_str(), 158, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfff);

	myBox.DrawBox(BLACK, MAGENTA);	// paddle
	myBorder.DrawBox(GREEN, NONE);	// border

}

APP_STATE GameState::next()
{
	if (bisGameOver) return ENTER_GAMEOVER;
	if (sfw::getKey(KEY_ESCAPE)) return ENTER_MENU;
	return GAME;
}