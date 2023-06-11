#pragma once
#include "raylib.h"

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	int Score = 0;

	bool CPU = false;

	Rectangle GetRect()
	{
		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
	}

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};