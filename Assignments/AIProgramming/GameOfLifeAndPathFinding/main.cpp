#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/GLU.h>

#include "camera.h"
#include "matrix.h"
#include "vector.h"

//#include "GameOfLife.h"
#include "PathFinding.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

int Dijkstra::currentDistance = 0;

// Simple camera controller. (MOUSE)
//Camera gCamera;

int main()
{
	int running = GL_TRUE;

	GLFWwindow* window;

	/* Initialize the GLFW library */
	if (!glfwInit())
		return -1;

	// Open an OpenGL window
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Hook window resize.
	glfwSetWindowSizeCallback(window, onWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	// hook mouse click callback.
	glfwSetMouseButtonCallback(window, OnMouseClick);
	// hook keyboard callback
	glfwSetKeyCallback(window, Key_Callback);

	//	glfwSwapInterval(1);

	init();
	AIStrategy* currentStrategy = new Dijkstra();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// OpenGL rendering goes here...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(viewportOffsetX, viewportOffsetY, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, width, height, 0, 0, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Check if ESC key was pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;

		MouseDrag(window);

		// =========================================================================================================
		//PATH FINDING

		if (changedStrategy == true)
		{
			if (strategyNum == 5)
			{
				delete currentStrategy;
				currentStrategy = new Dijkstra();
			}
			else if (strategyNum == 6)
			{
				delete currentStrategy;
				currentStrategy = new AStar();
			}
			changedStrategy = false;
		}

		if (findStart)
		{
			if (restartSearch == true)
			{
				restartSearch = false;
				currentStrategy->RestartFindPath(boxStatus);
			}
			currentStrategy->FindPath(boxStatus);
		}

		if (isReset == true)
		{
			currentStrategy->ResetCurrentBox(boxStatus);
			isReset = false;
		}

		// =========================================================================================================

		Display(window);
		/*
				if (startLife)
				{
					glfwSwapInterval(curTimeRate);
					LifeUpdate(map_height, map_width, state);
					glfwSwapBuffers(window);

					Display(window);
				}
		*/
		glfwSwapInterval(1);
		// Swap front and back rendering buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	delete currentStrategy;

	deinit();

	// Close window and terminate GLFW
	glfwTerminate();
}
