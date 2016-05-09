#include <GLFW/glfw3.h>
#include "Paddle.h"
#include <stdio.h>

Paddle::Paddle(int x, int y, int w, int h, int minX, int maxX, Color c) :
	xPos(x),
	yPos(y),
	xSpeed(0),
	height(h),
	width(w),
	originalWidth(w),
	minXLimit(minX),
	maxXLimit(maxX),
	maxSpeed(21),
	color(c) {}

int Paddle::getXPos() {
	return xPos;
}

int Paddle::getYPos() {
	return yPos;
}

int Paddle::getHeight() {
	return height;
}

int Paddle::getWidth() {
	return width;
}

int Paddle::getSpeed() {
	return xSpeed;
}

void Paddle::setXPos(int pos) {
	xPos = pos;
}

void Paddle::setYPos(int pos) {
	yPos = pos;
}

void Paddle::setSpeed(int speed) {
	xSpeed = speed;
}

int Paddle::getMaxSpeed() {
	return maxSpeed;
}

void Paddle::printState() {
	printf("Paddle:\nX Pos: %d\nY Pos: %d\nSpeed: %d\n\n", xPos, yPos, xSpeed);
}

void Paddle::changeSize(int newWidth, int frameCount) {
	sizeFrameCount = frameCount;
	width = newWidth;
}

void Paddle::update() {
	this->xPos += xSpeed;
	if (xPos < minXLimit) {
		this->xPos = minXLimit;
	}
	else if (xPos + width > maxXLimit) {
		this->xPos = maxXLimit - width;
	}
	if (sizeFrameCount > 0) {
		sizeFrameCount--;
		if (sizeFrameCount == 0) {
			width = originalWidth;
		}
	}
}

void Paddle::draw() {
	glColor3f(color.getR(), color.getG(), color.getB());

	glBegin(GL_QUADS);
	glVertex2i(xPos, yPos);
	glVertex2i(xPos + width, yPos);
	glVertex2i(xPos + width, yPos + height);
	glVertex2i(xPos, yPos + height);
	glEnd();
}
