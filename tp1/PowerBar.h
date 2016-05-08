#pragma once
#include "Color.h"

class PowerBar {
private:
	int screenWidth;
	int xPos, yPos, height;
	Color color;

public:
	PowerBar(int y, int height, int screenWidth, Color c);
	void setXPos(int x);
	void draw();
};