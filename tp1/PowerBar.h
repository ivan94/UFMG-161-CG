#pragma once
#include "Color.h"

class PowerBar {
private:
	int screenHeight;
	int xPos, yPos, width;
	Color color;

public:
	PowerBar(int x, int width, int screenHeight, Color c);
	void setYPos(int y);
	int getYPos();
	void draw();
};