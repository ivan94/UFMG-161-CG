#include <GLFW/glfw3.h>
#include "PowerBar.h"

PowerBar::PowerBar(int y, int height, int screenWidth, Color c) :
	yPos(y),
	height(height),
	screenWidth(screenWidth),
	xPos(screenWidth / 2),
	color(c) {}

void PowerBar::setXPos(int x) {
	xPos = x;
}

void PowerBar::draw() {
	int minX, maxX;

	if (xPos < screenWidth / 2) {
		minX = xPos;
		maxX = screenWidth / 2;
	}
	else {
		minX = screenWidth / 2;
		maxX = xPos;
	}
	glColor3f(color.getR(), color.getG(), color.getB());

	glBegin(GL_QUADS);
	glVertex2i(minX, yPos);
	glVertex2i(maxX, yPos);
	glVertex2i(maxX, yPos + height);
	glVertex2i(minX, yPos + height);
	glEnd();
}