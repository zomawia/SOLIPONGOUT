#include "Gamestate.h"
#include <string>


void GameState::CreateGameState()
{
	BallsLeft = 5;
	totalPoints = 0;
	myBall[5] = {};
	myPaddle = {};
	myBorder = {};
	bisGameOver = false;
	timer = 4;

	tonc_font = sfw::loadTextureMap("./res/tonc_font.png", 16, 6);

	// create balls in array with function

	for (int i = 0; i < 5; ++i)
	{
		myBall[i] = myBall[i].createBall(randomRange(16, WINDOW_WIDTH-16), randomRange(WINDOW_HEIGHT/2, WINDOW_HEIGHT-16), randomRange(-3, -1),
			randomRange(-3, -1), 16);
	}

	myPaddle = myPaddle.CreateBox(PADDLE_X_POS, PADDLE_Y_POS, paddleLength, paddleHeight);
	myBorder = myBorder.CreateBox(1, 1, WINDOW_WIDTH - 2, WINDOW_HEIGHT - 2);
	myBoss = myBoss.create();
	

}

void GameState::UpdateGameState()
{		
	bossTalkTimer -= sfw::getDeltaTime();
	if (bossTalkTimer > 0) myBoss.drawTalk(myBoss.getTalk(),tauntSelection);
	else myBoss.setTalk(IDLE);
	
	// stop updating if game over
	if (!bisGameOver)
	{
		myPaddle.UpdateBox();
	}	

	for (int i = 0; i < 5; ++i)
	{		//Update ball location
		myBall[i].UpdateBall();
	}

	myBoss.Update();

	// Collision stuff
	if (!bisGameOver)
	{
		for (int i = 0; i < 5; ++i)
		{
			//Ball collision for boundaries
			if (myBall[i].getPosition().y + myBall[i].getRadius() >= WINDOW_HEIGHT) // TOP
			{
				myBall[i].setPosition(myBall[i].getPosition().x, WINDOW_HEIGHT - myBall[i].getRadius());
				myBall[i].setVelocity(randomRange(-4, 4),
					-myBall[i].getVelocity().y + -(totalPoints / 200));
			}

			if (myBall[i].getPosition().x + myBall[i].getRadius() >= WINDOW_WIDTH)
			{
				myBall[i].setPosition(WINDOW_WIDTH - myBall[i].getRadius(), myBall[i].getPosition().y);
				myBall[i].setVelocity(-myBall[i].getVelocity().x, myBall[i].getVelocity().y);	// RIGHT
			}

			if (myBall[i].getPosition().x - myBall[i].getRadius() <= 0)
			{
				myBall[i].setPosition(myBall[i].getRadius(), myBall[i].getPosition().y);
				myBall[i].setVelocity(-myBall[i].getVelocity().x, myBall[i].getVelocity().y);	// LEFT
			}

			//Ball collision for paddle			
			if ((myBall[i].getPosition().y - myBall[i].getRadius() <= PADDLE_Y_POS + myPaddle.getDimension().y)
				&& !myBall[i].getOut())
			{
				// top of paddle
				if (myPaddle.isBoxColliding(myBall[i].getPosition().x, myBall[i].getPosition().y - myBall[i].getRadius()))
				{
					// set to clean Y to reduce stutter
					myBall[i].setPosition(myBall[i].getPosition().x, PADDLE_Y_POS + myBall[i].getRadius() + myPaddle.getDimension().y);

					if (myBall[i].getPosition().x <= myPaddle.getPosition().x + myPaddle.getDimension().x / 2)
						myBall[i].setVelocity(myBall[i].getVelocity().x, -myBall[i].getVelocity().y);
					else myBall[i].setVelocity(myBall[i].getVelocity().x, fabs(myBall[i].getVelocity().y));

					totalPoints++;
					//printf("Ball %d Collision at: %f %f \n", i, myBall[i].getPosition().x, myBall[i].getPosition().y - myBall[i].getRadius() );
					tauntSelection = randomRange(1, 3);
					myBoss.setTalk(TAUNT);
					bossTalkTimer = 3;

				}

				// left paddle
				else if (myPaddle.isBoxColliding(myBall[i].getPosition().x + myBall[i].getRadius(), myBall[i].getPosition().y))
				{
					myBall[i].setPosition(myBall[i].getPosition().x - myBall[i].getRadius(), myBall[i].getPosition().y);
					myBall[i].setVelocity(-myBall[i].getVelocity().x * 3, myBall[i].getVelocity().y);

				}

				// right paddle
				else if (myPaddle.isBoxColliding(myBall[i].getPosition().x - myBall[i].getRadius(), myBall[i].getPosition().y))
				{
					myBall[i].setPosition(myBall[i].getPosition().x + myBall[i].getRadius(), myBall[i].getPosition().y);
					myBall[i].setVelocity(-myBall[i].getVelocity().x * 3, myBall[i].getVelocity().y);
				}

				if (myBall[i].outBounds())
				{
					myBall[i].setOut();
					BallsLeft--;
				}
			}

			// ball on ball collision
			for (int j = i + 1; j < 5; ++j)
			{
				if (myBall[j].isColliding(myBall[i]))
				{
					myBall[j].doCollision(myBall[i]);
				}
			}

			// ball on boss collision
			if (myBall[i].isColliding(myBoss.getBall()))
			{
				myBall[i].setVelocity(-myBall[i].getVelocity().x, -myBall[i].getVelocity().y);
				myBoss.reduceHealth(10);
				myBall[i].reduceHealth(5);

				myBoss.setTalk(WEAK);
				bossTalkTimer = 3;

			}

			// respawn ball if stuck on boss
			if (myBall[i].getHealth() <= 0)
			{
				myBall[i] = myBall[i].createBall(randomRange(16, WINDOW_WIDTH - 16), randomRange(WINDOW_HEIGHT / 2, WINDOW_HEIGHT - 16), randomRange(-3, -1),
					randomRange(-3, -1), 24);
			}

			// boss killed get points and respawn boss
			if (myBoss.getBall().getHealth() <= 0)
			{
				timer -= sfw::getDeltaTime();
				myBoss.setTalk(DEAD);
				if (timer <= 0)
				{
					totalPoints += 20;
					myBoss = myBoss.create();
					timer = 3;
				}

			}

		}
	}
	
	if (BallsLeft <= 0 || myPaddle.isBoxColliding(myBoss.GetLaser().getPosition().x + myBoss.GetLaser().getDimension().x,
		myBoss.GetLaser().getPosition().y) )
	{
		myBoss.setTalk(VICTORY);
		bossTalkTimer = 3;
		bisGameOver = true;
	}
}

void GameState::DrawGameState()
{
	if (bisSoliActivate == true)
	{
		char buffer[64];
		sprintf_s(buffer, "SOLIPONGOUT");

		sfw::drawString(tonc_font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 50), randomRange(14, 60), randomRange(0, 360), 0, BLACK);
		sfw::drawString(tonc_font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 60), randomRange(0, 360), 0, RED);
		sfw::drawString(tonc_font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 50), randomRange(14, 60), randomRange(0, 360), 0, BLACK);
		sfw::drawString(tonc_font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 60), randomRange(0, 360), 0, RED);
		sfw::drawString(tonc_font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 50), randomRange(14, 60), randomRange(0, 360), 0, BLACK);
		sfw::drawString(tonc_font, buffer, randomRange(0, WINDOW_WIDTH), randomRange(0, WINDOW_HEIGHT),
			randomRange(1, 70), randomRange(14, 60), randomRange(0, 360), 0, RED);
	}
	
	for (int i = 0; i < 5; ++i)
	{
		// Draw Ball
		sfw::drawCircle(myBall[i].getPosition().x, myBall[i].getPosition().y, myBall[i].getRadius(), 16, BLACK);
		myBall[i].drawColorBall(myBall[i].getRadius());
	}

	myBoss.Draw();

	// Draw Background
	sfw::setBackgroundColor(WHITE);
	sfw::drawTexture(background, 0, 600, 800, 600, 0, false, 0, 0x8888880F);

	// Draw Score	
	if (totalPoints < 10) sfw::drawString(tonc_font, std::to_string(totalPoints).c_str(), 
		WINDOW_WIDTH / 2 - 140, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);
	else sfw::drawString(tonc_font, std::to_string(totalPoints).c_str(), 
		WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 + 150, 300, 300, 0, ' ', 0xbfbfbf31);

	if (!bisGameOver) 
	{
		sfw::drawString(tonc_font, "BALLS:", 5, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfaf);
		sfw::drawString(tonc_font, std::to_string(BallsLeft).c_str(), 158, WINDOW_HEIGHT - 5, 24, 24, 0, ' ', 0xbfbfbfff);
		myPaddle.DrawBox(BLACK, BLUE);	// paddle
	}

	
	myBorder.DrawBox(GREEN, NONE);	// border

	//printf("x: %f, y: %f\n", myPaddle.getPosition().x, myPaddle.getPosition().y);

}

APP_STATE GameState::next()
{
	if (bisGameOver) return ENTER_GAMEOVER;
	if (sfw::getKey(KEY_ESCAPE)) return ENTER_MENU;
	return GAME;
}