#include <stdio.h>
#include <vector>
#include <cstring>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "fmod.hpp"
#include "common.h"
#include "Brick.h"
#include "Color.h"
#include "Paddle.h"
#include "Ball.h"
#include "SpeedBar.h"
#include "PowerBar.h"
#include "Text2D.h"
#include "Text.h"

#define SCREENWIDTH 854
#define SCREENHEIGHT 480

bool GLOBAL_FINISHGAME = false;
bool GLOBAL_GAMEPAUSED = true;
bool GLOBAL_SETGAMETOPAUSE = false;

std::vector<Brick> bricks;
Paddle paddle(377, 460, 100, 10, 0, SCREENWIDTH, Color(0.655f, 0.063f, 0.761f));
Text score(4, 4, (char*)"Score: %d", Color(1, 1, 1));
Ball ball(422, 450, 10, SCREENWIDTH, SCREENHEIGHT, Color::white());
SpeedBar speedbar(470, 10, SCREENWIDTH, Color(1.0f, 1.0f, 0.0f));
PowerBar powerbar(844, 10, SCREENHEIGHT, Color::red());

double gameTime;
int windowWidth = SCREENWIDTH;
int windowHeight = SCREENHEIGHT;

int fps;
int pts = 0;

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
	ball.setMinSpeed(1.42f);
	ball.setMaxSpeed(7.25f);
	ball.setSpeed(0.5f);
}

void printGameState() {
	int i = 0;

	for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); it++) {
		(*it).printState(i);
		i++;
	}
	printf("\n");
	paddle.printState();
	ball.printState();
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
	int midScreen = windowWidth / 2;
	paddle.setSpeed((int)(((xpos - midScreen) / midScreen) * paddle.getMaxSpeed()));
	speedbar.setXPos((int)((xpos / windowWidth) * SCREENWIDTH));
	powerbar.setYPos((int)((ypos / windowHeight) * SCREENHEIGHT));
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

void testSoundLib(){
	FMOD::System     *system;
    FMOD::Sound      *sound, *sound_to_play;
    FMOD::Channel    *channel = 0;
    FMOD_RESULT       result;
    unsigned int      version;
    void             *extradriverdata = 0;
    int               numsubsounds;

    Common_Init(&extradriverdata);

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    ERRCHECK(result);

    /*
        This example uses an FSB file, which is a preferred pack format for fmod containing multiple sounds.
        This could just as easily be exchanged with a wav/mp3/ogg file for example, but in this case you wouldnt need to call getSubSound.
        Because getNumSubSounds is called here the example would work with both types of sound file (packed vs single).
    */

    result = system->createStream(Common_MediaPath("htt.mp3"), FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
    ERRCHECK(result);

    result = sound->getNumSubSounds(&numsubsounds);
    ERRCHECK(result);

    if (numsubsounds)
    {
        sound->getSubSound(0, &sound_to_play);
        ERRCHECK(result);
    }
    else
    {
        sound_to_play = sound;
    }

    /*
        Play the sound.
    */
    result = system->playSound(sound_to_play, 0, false, &channel);
    ERRCHECK(result);

    /*
        Main loop.
    */
    do
    {
        Common_Update();

        if (Common_BtnPress(BTN_ACTION1))
        {
            bool paused;
            result = channel->getPaused(&paused);
            ERRCHECK(result);
            result = channel->setPaused(!paused);
            ERRCHECK(result);
        }

        result = system->update();
        ERRCHECK(result);

        {
            unsigned int ms = 0;
            unsigned int lenms = 0;
            bool         playing = false;
            bool         paused = false;

            if (channel)
            {
                result = channel->isPlaying(&playing);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
                {
                    ERRCHECK(result);
                }

                result = channel->getPaused(&paused);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
                {
                    ERRCHECK(result);
                }

                result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
                {
                    ERRCHECK(result);
                }

                result = sound_to_play->getLength(&lenms, FMOD_TIMEUNIT_MS);
                if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE))
                {
                    ERRCHECK(result);
                }
            }

            Common_Draw("==================================================");
            Common_Draw("Play Stream Example.");
            Common_Draw("Copyright (c) Firelight Technologies 2004-2016.");
            Common_Draw("==================================================");
            Common_Draw("");
            Common_Draw("Press %s to toggle pause", Common_BtnStr(BTN_ACTION1));
            Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
            Common_Draw("");
            Common_Draw("Time %02d:%02d:%02d/%02d:%02d:%02d : %s", ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 100, lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100, paused ? "Paused " : playing ? "Playing" : "Stopped");
        }

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    /*
        Shut down
    */
    result = sound->release();  /* Release the parent, not the sound that was retrieved with getSubSound. */
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    Common_Close();
}

int main(int argc, const char* argv[]) {
	testSoundLib();
	double timeElapsed;
	int fpsCounter = 0;
	GLFWwindow* window;

	glutInit(&argc, (char **)argv);

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
			if (ball.collisionDetection(paddle)) {
				ball.setSpeed(1.0f - ((float)powerbar.getYPos() / (float)SCREENHEIGHT));
			}
			for (std::vector<Brick>::iterator it = bricks.begin(); it != bricks.end(); it++) {
				if (ball.collisionDetection(*it)) {
					if ((*it).hit()) {
						pts++;
						score.setValue(pts);
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
		speedbar.draw();
		powerbar.draw();
		score.draw();

		glfwSwapBuffers(window);

		//Used for successive right mouse clicks
		if (GLOBAL_SETGAMETOPAUSE) {
			GLOBAL_SETGAMETOPAUSE = false;
			GLOBAL_GAMEPAUSED = true;
			printGameState();
		}
		//Framerate control
		timeElapsed = glfwGetTime() - gameTime;
		if (timeElapsed < 1) {
			fpsCounter++;
		}
		else {
			fps = fpsCounter;
			fpsCounter = 0;
			gameTime = glfwGetTime();
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
