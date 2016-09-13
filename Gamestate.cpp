#include "Gamestate.h"
#include <string>


GameState GameState::CreateGameState()
{
	GameState temp;

	// create balls in array with function

	for (int i = 0; i < 5; ++i)
	{
		temp.myBall[i] = temp.myBall[i].createBall(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, randomRange(-3, -1), randomRange(8, 24));
	}

	temp.myBox = temp.myBox.CreateBox(PADDLE_X_POS, PADDLE_Y_POS, WINDOW_WIDTH / 4, 12);
	temp.myBorder = temp.myBox.CreateBox(1, 1, WINDOW_WIDTH - 2, WINDOW_HEIGHT - 2);

	return temp;
}

void GameState::UpdateGameState(GameState & gs)
{
	// stop updating if game over
	if (!gs.bisGameOver)
	{
		gs.myBox.UpdateBox(gs.myBox);
	}
	else sfw::drawString(gs.f, "GAME OVER", 180, WINDOW_HEIGHT - 55, 50, 50, 0, ' ', 0xbfbfbfff);

	// Collision stuff
	for (int i = 0; i < 5; ++i)
	{
		//Update ball location
		gs.myBall[i].UpdateBall();

		//Ball collision for boundaries
		if (gs.myBall[i].getPosition().y + gs.myBall[i].getRadius() >= WINDOW_HEIGHT) // TOP
		{
			gs.totalPoints++;
			//gs.myBall[i].setVelocityMult(.05f + gs.myBall[i].getVelocityMult);
			gs.myBall[i].setVelocity(randomRange(-3, 3), -gs.myBall[i].getVelocity().y);// +gs.myBall[i].getVelocityMult);
																						//gs.myBall[i].setVelocity.y *= -(1 + gs.myBall[i].getVelocityMult);
		}
		if (gs.myBall[i].getPosition().x + gs.myBall[i].getRadius() >= WINDOW_WIDTH)
			gs.myBall[i].setVelocity(-gs.myBall[i].getVelocity().x, gs.myBall[i].getVelocity().y);	// RIGHT
		if (gs.myBall[i].getPosition().x - gs.myBall[i].getRadius() <= 0)
			gs.myBall[i].setVelocity(-gs.myBall[i].getVelocity().x, gs.myBall[i].getVelocity().y);	// LEFT


																									//Ball collision for paddle			
		if (gs.myBall[i].getPosition().y - gs.myBall[i].getRadius() <= PADDLE_Y_POS + gs.myBox.getDimension().y
			&& !gs.myBall[i].outBounds())
		{
			if (gs.myBall[i].getPosition().x >= gs.myBox.getPosition().x &&
				gs.myBall[i].getPosition().x <= gs.myBox.getPosition().x + gs.myBox.getDimension().x)
			{
				gs.myBall[i].setPosition(gs.myBall[i].getPosition().x,
					gs.myBall[i].getPosition().y + gs.myBox.getDimension().y);
				gs.myBall[i].setVelocity(gs.myBall[i].getVelocity().x, -gs.myBall[i].getVelocity().y);
			}

			else if (!gs.myBall[i].outBounds() && !gs.myBall[i].getOut() )
			{
				gs.myBall[i].setOut();
				gs.BallsLeft--;
			}
		}

	}

	if (gs.BallsLeft <= 0)
	{
		gs.bisGameOver = true;
	}
}

void GameState::DrawGameState(GameState & gs)
{
	for (int i = 0; i < 5; ++i)
	{
		// Draw Ball
		sfw::drawCircle(gs.myBall[i].getPosition().x, gs.myBall[i].getPosition().y, gs.myBall[i].getRadius(), 16, BLACK);
	}

	// Draw Background
	sfw::setBackgroundColor(WHITE);
	sfw::drawTexture(gs.r, 0, 600, 800, 600, 0, false, 0, 0x8888880F);

	// Draw Score
	if (gs.totalPoints < 10) sfw::drawString(gs.f, std::to_string(gs.totalPoints).c_str(), WINDOW_WIDTH / 2 - 140, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);
	else sfw::drawString(gs.f, std::to_string(gs.totalPoints).c_str(), WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);

	sfw::drawString(gs.f, "BALLS:", 5, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfaf);
	sfw::drawString(gs.f, std::to_string(gs.BallsLeft).c_str(), 158, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfff);

	gs.myBox.DrawBox(gs.myBox, BLACK, MAGENTA);	// paddle
	gs.myBorder.DrawBox(gs.myBorder, GREEN, NONE);	// border

}
