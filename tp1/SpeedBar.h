#pragma once
#include "Color.h"

class SpeedBar {
private:
	int screenWidth;
	int xPos, yPos, height;
	Color color;

public:
	SpeedBar(int y, int height, int screenWidth, Color c);
	void setXPos(int x);
	void draw();
};