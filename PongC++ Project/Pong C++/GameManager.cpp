#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include "raylib.h"
#include "GameManager.h"


void GameManager::InitGame()
{

	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 150;
	ball.speedY = 150;

	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	while (!WindowShouldClose())
	{
		switch (GS)
		{
		case MENU:
			MainMenu();
			break;

		case BASIC_GAME:
			StartGame();
			break;
		
		case QUIT:
			return;
			
		}
	}
}

void GameManager::MainMenu()
{
		int textWidth0 = MeasureText("Pong C++", 60);
		int TextoffsetY = -140;

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Pong C++", GetScreenWidth() / 2 - textWidth0 / 2, GetScreenHeight() / 2 + TextoffsetY, 60, RAYWHITE);


		if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 120,(float)GetScreenHeight() / 2, 230,60 }, "Play Classic 2P"))
		{
			GS = BASIC_GAME;
			//GameStarted = true;
			ClearBackground(BLACK);
		}

		if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 120,(float)GetScreenHeight() / 2 + 70 , 230,60 }, "Play Classic CPU"))
		{
			GS = BASIC_GAME;
			rightPaddle.CPU = true;
			//GameStarted = true;
			ClearBackground(BLACK);
		}

		//if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 120,(float)GetScreenHeight() / 2 + 140 , 230,60 }, "Explosive Pong"))
		//{
		//	GS = EXPLOSIVE_GAME;
		//	rightPaddle.CPU = true;
		//	//GameStarted = true;
		//	ClearBackground(BLACK);
		//}

		if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 120,(float)GetScreenHeight() / 2 + 210, 230,60 }, "Exit"))
		{
			GS = QUIT;
		}

		EndDrawing();
}

void GameManager::PauseMenu()
{
	GamePaused = !GamePaused;

	while (GamePaused)
	{
		SetTargetFPS(0);
		int offsetX = 120;
		BeginDrawing();
		DrawText("PAUSED", GetScreenWidth() / 2 - offsetX , GetScreenHeight() / 2 - offsetX ,60, RAYWHITE);
		
		if (GuiButton(Rectangle{ (float)GetScreenWidth() / 2 - 120,(float)GetScreenHeight() / 2, 230,60 }, "Main Menu"))
		{
			GS = MENU;
			//GameStarted = false;
			GamePaused = false;
			SetTargetFPS(60);
			ClearBackground(BLACK);
			
		}
		
		EndDrawing();

		if (IsKeyPressed(KEY_P))
		{
			SetTargetFPS(60);
			GamePaused = false;
			GS = QUIT;
		}
	}
}

void GameManager::StartGame()
{
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();
		
		if (leftPaddle.y < 0)
		{
			leftPaddle.y = 0;
		}
		if (leftPaddle.y > GetScreenHeight())
		{
			leftPaddle.y = GetScreenHeight();
		}
		if (rightPaddle.y < 0)
		{
			rightPaddle.y = 0;
		}
		if (rightPaddle.y > GetScreenHeight())
		{
			rightPaddle.y = GetScreenHeight();
		}
		
		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speedY *= -1;
		}
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}
		if (IsKeyPressed(KEY_P))
		{
			PauseMenu();
		}
		if (IsKeyDown(KEY_W))
		{
			leftPaddle.y -= leftPaddle.speed * GetFrameTime();
		}
		if (IsKeyDown(KEY_S))
		{
			leftPaddle.y += leftPaddle.speed * GetFrameTime();
		}


		if (rightPaddle.CPU == false)
		{
			if (IsKeyDown(KEY_UP))
			{
				rightPaddle.y -= rightPaddle.speed * GetFrameTime();
			}
			if (IsKeyDown(KEY_DOWN))
			{
				rightPaddle.y += rightPaddle.speed * GetFrameTime();
			}
		}
		else if (rightPaddle.CPU && ball.x > 400.0f)
		{
			// Calculate the difference between the ball's y-coordinate and the current y-coordinate of the right paddle
			float yDifference = ball.y - rightPaddle.y;


			// Move the right paddle towards the ball's y-coordinate gradually
			if (yDifference > 0)
			{
				rightPaddle.y += rightPaddle.speed;
				if (rightPaddle.y > ball.y)
					rightPaddle.y = ball.y;
			}
			else if (yDifference < 0)
			{
				rightPaddle.y -= rightPaddle.speed;
				if (rightPaddle.y < ball.y)
					rightPaddle.y = ball.y;
			}
		}


		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, rightPaddle.GetRect()))
		{
			if (ball.speedX > 0)
			{
				ball.speedX *= - 1.0f;
				ball.speedY *= .8f; //(ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, leftPaddle.GetRect()))
		{
			if (ball.speedX < 0)
			{
				ball.speedX *= - 1.0f;
				ball.speedY *= .8f; //(ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}

		if (ball.x < 0)
		{
			if (rightPaddle.Score < 10-1)
			{
				rightPaddle.Score++;

				ball.x = GetScreenWidth() / 2;
				ball.y = GetScreenHeight() / 2;
				ball.speedX = 300;
				ball.speedY = 300;
			}
			else if (rightPaddle.Score >= 10 - 1)
			{
				rightPaddle.Score = 10;
				winnerText = "P2 Player Wins!";
			}
		}

		if (ball.x > GetScreenWidth())
		{
			if (leftPaddle.Score < 10-1)
			{
				leftPaddle.Score++;

				ball.x = GetScreenWidth() / 2;
				ball.y = GetScreenHeight() / 2;
				ball.speedX = 300;
				ball.speedY = 300;
			}
			else if (leftPaddle.Score >= 10 - 1)
			{
				leftPaddle.Score = 10;
				winnerText = "P1 Player Wins!";
			}
		}

		if (winnerText && IsKeyPressed(KEY_SPACE))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			leftPaddle.Score = 0;
			rightPaddle.Score = 0;
			winnerText = nullptr;
		}
		BeginDrawing();
		ClearBackground(BLACK);

		

		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();

		//Draw Score Text LEFT
		DrawText(TextFormat("P1: %02i", leftPaddle.Score), GetScreenWidth() / 2  - 350, GetScreenHeight() / 2 - 250 , 30, RAYWHITE);
		//Draw Score Text RIGHT
		DrawText(TextFormat("P2: %02i", rightPaddle.Score), GetScreenWidth() / 2 + 250, GetScreenHeight() / 2 - 250, 30, RAYWHITE);

		if (winnerText)
		{
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2, 60, YELLOW);
		}

		DrawFPS(10, 10);

		EndDrawing();
}
