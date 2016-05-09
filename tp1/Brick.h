#pragma once
#include "Color.h"

class Brick {
private:
	int xPos, yPos;
	int height, width;
	int lives;
	bool indestructible;
	Color color;

public:
	Brick(int x, int y, int w, int h, Color c);
	int getXPos();
	int getYPos();
	void setXPos(int xPos);
	void setLives(int lives);
	int getHeight();
	int getWidth();
	void setColor(Color c);
	void setIndestructible(bool ind);
	bool hit();
	void printState(int i);
	void draw();
};