#include <GLFW/glfw3.h>
#include "Ball.h"
#include <stdio.h>
Ball::Ball(int x, int y, int size, int screenW, int screenH, Color c) :
	xPos(x),
	yPos(y),
	size(size),
	screenHeight(screenH),
	screenWidth(screenW),
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

void Ball::setXSpeed(int speed) {
	xSpeed = speed;
}

void Ball::setYSpeed(int speed) {
	ySpeed = speed;
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

void Ball::update() {
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
		yPos = screenHeight - size;
		ySpeed *= -1;
	}
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