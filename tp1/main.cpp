#include <stdio.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "Brick.h"
#include "Color.h"
#include "Paddle.h"
#include "Ball.h"
#include "PowerBar.h"

#define SCREENWIDTH 854
#define SCREENHEIGHT 480

bool GLOBAL_FINISHGAME = false;
bool GLOBAL_GAMEPAUSED = true;
bool GLOBAL_SETGAMETOPAUSE = false;

std::vector<Brick> bricks;
Paddle paddle(377, 460, 100, 10, 0, SCREENWIDTH, Color(0.655f, 0.063f, 0.761f));
Ball ball(422, 450, 10, SCREENWIDTH, SCREENHEIGHT, Color::white());
PowerBar powerbar(470, 10, SCREENWIDTH, Color(1.0f, 1.0f, 0.0f));

double gameTime;
int windowWidth = SCREENWIDTH;
int windowHeight = SCREENHEIGHT;

void initBrickWall() {
	int i, j;
	int brickWidth = 50;
	int brickHeight = 20;
	int gapX = 6;
	int gapY = 6;
	int brickX, brickY;

	if (!bricks.empty()) {
		bricks.clear();
	}

	for (i = 0; i < 5; i++) {
		brickY = gapY + i * (gapY + brickHeight);
		for (j = 0; j < 15; j++) {
			brickX = gapX + j * (gapX + brickWidth);
			bricks.push_back(Brick(brickX, brickY, brickWidth, brickHeight, Color::blue()));
		}
	}

	//Some indestructible bricks
	bricks[4 * 15 + 7].setIndestructible(true);
	bricks[4 * 15 + 7].setColor(Color(0.5f, 0.5f, 0.5f));
	bricks[2 * 15 + 5].setIndestructible(true);
	bricks[2 * 15 + 5].setColor(Color(0.5f, 0.5f, 0.5f));
	bricks[2 * 15 + 9].setIndestructible(true);
	bricks[2 * 15 + 9].setColor(Color(0.5f, 0.5f, 0.5f));
	bricks[4 * 15 + 3].setIndestructible(true);
	bricks[4 * 15 + 3].setColor(Color(0.5f, 0.5f, 0.5f));
	bricks[4 * 15 + 11].setIndestructible(true);
	bricks[4 * 15 + 11].setColor(Color(0.5f, 0.5f, 0.5f));

}

void restartGame() {
	GLOBAL_GAMEPAUSED = true;
	initBrickWall();
	paddle.setSpeed(0);
	paddle.setXPos(377);
	ball.setXPos(422);
	ball.setYPos(450);
	ball.setXSpeed(3);
	ball.setYSpeed(-3);
}

void printGameState() {
	int i = 0;

	for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); it++) {
		printf("Brick %d: X Pos: %d Y Pos: %d\n", i, (*it).getXPos(), (*it).getYPos());
		i++;
	}
	printf("\n");
	printf("Paddle:\nX Pos: %d\nY Pos: %d\nSpeed: %d\n\n", paddle.getXPos(), paddle.getYPos(), paddle.getSpeed());
	printf("Ball:\nX Pos: %d\nY Pos: %d\n\n", ball.getXPos(), ball.getYPos());
}

void mousebutton_callback(GLFWwindow* window, int button, int action, int mods) {
	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		if (action == GLFW_PRESS) {
			GLOBAL_GAMEPAUSED = !GLOBAL_GAMEPAUSED;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		if (action == GLFW_PRESS) {
			if (!GLOBAL_GAMEPAUSED) {
				GLOBAL_GAMEPAUSED = true;
				printGameState();
			}
			else {
				GLOBAL_SETGAMETOPAUSE = true;
				GLOBAL_GAMEPAUSED = false;
			}
		}
		break;
	}
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos) {
	paddle.setSpeed((int)((xpos - windowWidth / 2)*0.05));
	powerbar.setXPos((int)((xpos / windowWidth)*SCREENWIDTH));
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
}

void character_callback(GLFWwindow *window, unsigned int codepoint) {
	switch (codepoint) {
	case 'q':
	case 'Q':
		GLOBAL_FINISHGAME = true;
		break;
	case 'r':
	case 'R':
		restartGame();
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
	glfwSetCursorPosCallback(*window, cursor_callback);
	glfwSetMouseButtonCallback(*window, mousebutton_callback);
	glfwSwapInterval(1);

	return true;
}

void clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
}

int main() {
	double timeElapsed;
	int fpsCounter = 0;
	GLFWwindow* window;
	
	if (!initGL(&window)) {
		return -1;
	}

	restartGame();
	gameTime = glfwGetTime();

	while (!glfwWindowShouldClose(window) && !GLOBAL_FINISHGAME) {
		clearScreen();

		glfwPollEvents();

		if (!GLOBAL_GAMEPAUSED) {
			paddle.update();
			ball.update();
			ball.collisionDetection(paddle);
			for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); it++) {
				if (ball.collisionDetection(*it)) {
					if ((*it).hit()) {
						it = bricks.erase(it);
					}
					break;
				}
			}
		}

		for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); it++) {
			(*it).draw();
		}

		paddle.draw();
		ball.draw();
		powerbar.draw();

		glfwSwapBuffers(window);

		//Framerate control
		timeElapsed = glfwGetTime() - gameTime;
		if (timeElapsed < 1) {
			fpsCounter++;
		}
		else {
			printf("%d fps\n", fpsCounter);
			fpsCounter = 0;
			gameTime = glfwGetTime();
		}
		
		if (GLOBAL_SETGAMETOPAUSE) {
			GLOBAL_SETGAMETOPAUSE = false;
			GLOBAL_GAMEPAUSED = true;
			printGameState();
		}
		//Loop for paused game
		while (GLOBAL_GAMEPAUSED) {
			//Game is unpaused when the left mouse button is pressed
			glfwWaitEvents();
			if (glfwWindowShouldClose(window) || GLOBAL_FINISHGAME) {
				break;
			}
		}
	}

	glfwTerminate();
	return 0;
}