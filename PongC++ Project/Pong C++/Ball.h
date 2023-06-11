#pragma once
#include "raylib.h"

struct Ball
{
	float x, y;
	float speedX, speedY;
	float radius;

	Color BallColor = RAYWHITE;

	void Draw()
	{
		DrawCircle((int)x, (int)y, radius, BallColor);
	}
};