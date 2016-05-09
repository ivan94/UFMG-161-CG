#pragma once
#include "Color.h"
#include "Paddle.h"
#include "Brick.h"

class Ball {
private:
	int xPos, yPos;
	float speed, minSpeed, maxSpeed;
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
	void setSpeed(float speed);
	void setMinSpeed(float speed);
	void setMaxSpeed(float speed);
	float getSpeed();
	int getXSpeed();
	int getYSpeed();
	int getSize();
	bool collisionDetection(Paddle &p);
	bool collisionDetection(Brick &b);
	void printState();
	bool update();
	void draw();
};