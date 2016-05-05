#include <GLFW/glfw3.h>
#include "Brick.h"

Brick::Brick(int x, int y, int w, int h, Color c) :
	xPos(x),
	yPos(y),
	height(h),
	width(w),
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

void Brick::draw() {
	glColor3f(color.getR(), color.getG(), color.getB());

	glBegin(GL_QUADS);
	glVertex2i(xPos, yPos);
	glVertex2i(xPos + width, yPos);
	glVertex2i(xPos + width, yPos + height);
	glVertex2i(xPos, yPos + height);
	glEnd();
}