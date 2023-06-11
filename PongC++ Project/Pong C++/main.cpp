#include "raylib.h"

#include "GameManager.h"
#include "Paddle.h"
#include "Ball.h"
#include "GameManager.h"

int main()
{
	InitWindow(800,600,"Pong C++ | David Shannon");
	SetWindowState(FLAG_VSYNC_HINT);
	SetTargetFPS(60);

	GameManager GM;
	GM.InitGame();

	CloseWindow();
	return 0;
}