#include <GLFW/glfw3.h>
#include "Brick.h"
#include <stdio.h>

Brick::Brick(int x, int y, int w, int h, Color c) :
	xPos(x),
	yPos(y),
	height(h),
	width(w),
	lives(1),
	indestructible(false),
	color(c) {}

int Brick::getXPos() {
	return xPos;
}

int Brick::getYPos() {
	return yPos;
}

int Brick::getHeight() {
	return height;
}

int Brick::getWidth() {
	return width;
}

void Brick::setXPos(int xPos) {
	this->xPos = xPos;
}

void Brick::setLives(int lives) {
	this->lives = lives;
}

void Brick::setColor(Color c) {
	color = c;
}

void Brick::setIndestructible(bool ind) {
	indestructible = ind;
}

bool Brick::hit() {
	if (indestructible) {
		return false;
	}
	if (lives <= 1) {
		return true;
	}
	else {
		lives--;
		switch (lives){
		case 2:
			color = Color(.0f, .5f, 1.0f);
			break;
		case 1:
			color = Color(.5f, 1.0f, 1.0f);
			break;
		}
	}
	return false;
}

void Brick::printState(int i) {
	printf("Brick %d: X Pos: %d Y Pos: %d", i, xPos, yPos);
	if (indestructible) {
		printf(" (Indestructible)");
	}
	printf("\n");
}

void Brick::draw() {
	glColor3f(color.getR(), color.getG(), color.getB());

	glBegin(GL_QUADS);
	glVertex2i(xPos, yPos);
	glVertex2i(xPos + width, yPos);
	glVertex2i(xPos + width, yPos + height);
	glVertex2i(xPos, yPos + height);
	glEnd();
}