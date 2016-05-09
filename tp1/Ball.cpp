#include <GLFW/glfw3.h>
#include "Ball.h"
#include <stdio.h>

#define SQRT2 1.4142f

Ball::Ball(int x, int y, int size, int screenW, int screenH, Color c) :
	xPos(x),
	yPos(y),
	xSpeed(1),
	ySpeed(1),
	screenWidth(screenW),
	screenHeight(screenH),
	size(size),
	color(c) {}

int Ball::getXPos() {
	return xPos;
}

int Ball::getYPos() {
	return yPos;
}

void Ball::setXPos(int xPos) {
	this->xPos = xPos;
}

void Ball::setYPos(int yPos) {
	this->yPos = yPos;
}

//Receives a float from 0.0 to 1.0 that will be converted from minSpeed to maxSpeed
void Ball::setSpeed(float speed) {
	if (speed < 0.0f) {
		speed = 0.0f;
	}
	else if (speed > 1.0f) {
		speed = 1.0f;
	}

	speed *= (maxSpeed - minSpeed);
	speed += minSpeed;

	this->speed = speed;

	if (xSpeed > 0) {
		xSpeed = (int)(speed / SQRT2);
	}
	else {
		xSpeed = (int)(speed / SQRT2 * -1);
	}

	if (ySpeed > 0) {
		ySpeed = (int)(speed / SQRT2);
	}
	else {
		ySpeed = (int)(speed / SQRT2 * -1);
	}
}

void Ball::setMinSpeed(float speed) {
	this->minSpeed = speed;
}

void Ball::setMaxSpeed(float speed) {
	this->maxSpeed = speed;
}

float Ball::getSpeed() {
	return speed;
}

int Ball::getXSpeed() {
	return xSpeed;
}

int Ball::getYSpeed() {
	return ySpeed;
}

int Ball::getSize() {
	return size;
}

bool Ball::collisionDetection(Paddle &p) {
	if (xPos < p.getXPos() + p.getWidth() &&
		xPos + size > p.getXPos() &&
		yPos < p.getYPos() + p.getHeight() &&
		yPos + size > p.getYPos()) {

		//If the ball is higher than the paddle (or was higher in the last frame), the ball must be reflected
		if (yPos + size - ySpeed <= p.getYPos()) {
			ySpeed *= -1;
		}
		return true;
	}

	return false;
}

bool Ball::collisionDetection(Brick &b) {
	int oldTop, oldRight, oldBottom, oldLeft;

	if (xPos < b.getXPos() + b.getWidth() &&
		xPos + size > b.getXPos() &&
		yPos < b.getYPos() + b.getHeight() &&
		yPos + size > b.getYPos()) {

		oldTop = yPos - ySpeed;
		oldBottom = oldTop + size;
		oldLeft = xPos - xSpeed;
		oldRight = oldLeft + size;
		//Collided from bottom
		if (oldTop >= b.getYPos() + b.getHeight() && yPos <= b.getYPos() + b.getHeight()) {
			ySpeed *= -1;
		}
		//Collided from left
		else if (oldRight <= b.getXPos() && xPos + size >= b.getXPos()) {
			xSpeed *= -1;
		}
		//Collided from right
		else if (oldLeft >= b.getXPos() + b.getWidth() && xPos <= b.getXPos() + b.getWidth()) {
			xSpeed *= -1;
		}
		//Collided from top
		else if (oldBottom <= b.getYPos() && (yPos + size) >= b.getYPos()) {
			ySpeed *= -1;
		}

		return true;
	}

	return false;
}

void Ball::printState() {
	printf("Ball:\nX Pos: %d\nY Pos: %d\nSpeed: %.2f\nX Speed: %d\nY Speed: %d\n\n", xPos, yPos, speed, xSpeed, ySpeed);
}

bool Ball::update() {
	xPos += xSpeed;
	yPos += ySpeed;
	if (xPos < 0) {
		xPos = 0;
		xSpeed *= -1;
	}
	else if (xPos + size > screenWidth) {
		xPos = screenWidth - size;
		xSpeed *= -1;
	}
	if (yPos < 0) {
		yPos = 0;
		ySpeed *= -1;
	}
	else if (yPos + size > screenHeight) {
		return true;
	}

	return false;
}

void Ball::draw() {
	glColor3f(color.getR(), color.getG(), color.getB());

	glBegin(GL_QUADS);
	glVertex2i(xPos, yPos);
	glVertex2i(xPos + size, yPos);
	glVertex2i(xPos + size, yPos + size);
	glVertex2i(xPos, yPos + size);
	glEnd();
}
