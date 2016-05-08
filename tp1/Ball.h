#pragma once
#include "Color.h"
#include "Paddle.h"
#include "Brick.h"

class Ball {
private:
	int xPos, yPos;
	int xSpeed, ySpeed;
	int screenWidth, screenHeight;
	int size;
	Color color;

public:
	Ball(int x, int y, int size, int screenW, int screenH, Color c);
	int getXPos();
	int getYPos();
	void setXPos(int xPos);
	void setYPos(int yPos);
	void setXSpeed(int speed);
	void setYSpeed(int speed);
	int getSize();
	bool collisionDetection(Paddle &p);
	bool collisionDetection(Brick &b);
	void update();
	void draw();
};