#include <stdio.h>
#include <ctime>
#include <vector>
#include <GLFW/glfw3.h>
#include "Brick.h"
#include "Color.h"

#define SCREENWIDTH 854
#define SCREENHEIGHT 480

bool GLOBAL_FINISHGAME = false;

std::vector<Brick> bricks;
Brick paddle(377, 460, 100, 10, Color(0.655, 0.063, 0.761));

time_t t = time(NULL);
int count = 0;

int speed = 0;

void cursor_callback(GLFWwindow* window, double xpos, double ypos){
	speed = (int) ((xpos - SCREENWIDTH/2)*0.05);
}

void initBrickWall() {
	int i, j;
	int brickWidth = 50;
	int brickHeight = 20;
	int gapX = 6;
	int gapY = 6;
	int brickX, brickY;

	for (i = 0; i < 5; i++) {
		brickY = gapY + i * (gapY + brickHeight);
		for (j = 0; j < 15; j++) {
			brickX = gapX + j * (gapX + brickWidth);
			bricks.push_back(Brick(brickX, brickY, brickWidth, brickHeight, Color::blue()));
		}
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void character_callback(GLFWwindow *window, unsigned int codepoint) {
	switch (codepoint) {
	case 'q':
	case 'Q':
		GLOBAL_FINISHGAME = true;
		break;
	}
}

bool initGL(GLFWwindow** window) {
	if (!glfwInit()) {
		return false;
	}

	*window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "Breakout", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, SCREENWIDTH, SCREENHEIGHT, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);

	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);
	glfwSetCharCallback(*window, character_callback);

	return true;
}

void clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
}

int main() {
	GLFWwindow* window;

	if (!initGL(&window)) {
		return -1;
	}

	initBrickWall();
	glfwSetCursorPosCallback(window, cursor_callback);
	while (!glfwWindowShouldClose(window) && !GLOBAL_FINISHGAME) {
		clearScreen();

		for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); it++) {
			(*it).draw();
		}

		paddle.draw();

		glfwSwapBuffers(window);

		glfwPollEvents();

		paddle.setXPos(paddle.getXPos()+speed);

		if(t == time(NULL)){
			count++;
		}else{
			t = time(NULL);
			printf("%d fps\n", count);
			count = 0;
		}
	}

	glfwTerminate();
	return 0;
}
