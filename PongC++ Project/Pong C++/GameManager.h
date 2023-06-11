#pragma once
#include "Paddle.h"
#include "Ball.h"


class GameManager
{
public:

	GameManager() {}
	~GameManager() {}


	Ball ball;
	Paddle leftPaddle;
	Paddle rightPaddle;

	void InitGame();
	void MainMenu();
	void StartGame();
	void PauseMenu();

	bool GamePaused = false;
	bool GameStarted = false;
	const char* winnerText = nullptr;
	
	enum GameState
	{
		MENU,
		BASIC_GAME,
		QUIT
	};

	GameState GS = MENU;
};

