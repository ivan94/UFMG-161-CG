#pragma once
#include "Color.h"

class Paddle {
private:
	const int originalWidth;
	int xPos, yPos, xSpeed;
	int height, width;
	int minXLimit, maxXLimit;
	int maxSpeed;
	int sizeFrameCount;
	Color color;

public:
	Paddle(int x, int y, int w, int h, int minX, int maxX, Color c);
	int getXPos();
	int getYPos();
	int getSpeed();
	void setXPos(int pos);
	void setYPos(int pos);
	void setSpeed(int speed);
	int getMaxSpeed();
	int getHeight();
	int getWidth();
	void changeSize(int newWidth, int frameCounts);
	void printState();
	void update();
	void draw();
};