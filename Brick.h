#pragma once
#include "Color.h"

class Brick {
private:
	int xPos, yPos;
	int height, width;
	Color color;

public:
	Brick(int x, int y, int w, int h, Color c);
	int getXPos();
	int getYPos();
	int getHeight();
	int getWidth();
	void draw();
};