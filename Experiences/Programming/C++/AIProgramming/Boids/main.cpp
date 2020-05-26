#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/GLU.h>

#include "camera.h"
#include "matrix.h"
#include "vector.h"

//#include "GameOfLife.h"
//#include "PathFinding.h"
//#include "Steer.h"
#include "Boids.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

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

	init(window);
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// OpenGL rendering goes here...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
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
		

		// =========================================================================================================

		Display(window);

		glfwSwapInterval(1);
		// Swap front and back rendering buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	deinit();

	// Close window and terminate GLFW
	glfwTerminate();
}
