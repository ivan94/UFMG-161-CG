#include <GLFW/glfw3.h>
#include "PowerBar.h"

PowerBar::PowerBar(int x, int width, int screenHeight, Color c) :
	xPos(x),
	yPos(screenHeight),
	screenHeight(screenHeight),
	width(width),
	color(c) {}

void PowerBar::setYPos(int y) {
	yPos = y;
}

int PowerBar::getYPos() {
	return yPos;
}

void PowerBar::draw() {
	glColor3f(color.getR(), color.getG(), color.getB());

	glBegin(GL_QUADS);
	glVertex2i(xPos, yPos);
	glVertex2i(xPos + width, yPos);
	glVertex2i(xPos + width, screenHeight);
	glVertex2i(xPos, screenHeight);
	glEnd();
}