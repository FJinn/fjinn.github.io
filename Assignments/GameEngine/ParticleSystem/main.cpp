#include <GLFW/glfw3.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <GL/GLU.h>

#include "Application.h"

const int RESOLUTION_X = 640;
const int RESOLUTION_Y = 480;

#define TEXTURE_COUNT 6
GLuint GtextureID[TEXTURE_COUNT];

void gameUpdate(float deltaTime)
{
	std::cout << "delta time : " << deltaTime << std::endl;
}

void loadTexture(const char* path, GLuint textureID)
{
	CBitmap bitmap(path);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// use ortho 2D view
	gluOrtho2D(0, width, 0, height);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glGenTextures(TEXTURE_COUNT, GtextureID);
	loadTexture("../Media/tree.bmp", GtextureID[0]);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Hook window resize.
	glfwSetWindowSizeCallback(window, onWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized(window, RESOLUTION_X, RESOLUTION_Y);

	glfwSwapInterval(1); //enable/disable vsync

	// ==================================     Application    ==================================
	Application myApp;
	myApp.Start();

	// ================================== FPS and Delta Time ==================================

	// cache previous time
	double previousTime = glfwGetTime();
	double maxFPS = 60;
	double minDeltaTime = 1.0 / maxFPS;

/*	// cache begin time
//	double initialTime = glfwGetTime();
	// cache elapsed time
//	double elapsedTime = 0;
	// cache count frame
//	double countedFrame = 0;
*/
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


// ================================== FPS and Delta Time ==================================
#pragma region FPS and Delta Time
		//==== calculate delta time & fps
		// get current time
		double currentTime = glfwGetTime();
		// get the difference between current time and previous time
		double deltaTime = currentTime - previousTime;

		// conservatively asking the system to sleep
		if (deltaTime < minDeltaTime)
		{
			int sleepTime = (minDeltaTime - deltaTime) * 1000;
			if (sleepTime >= 10)
				Sleep(sleepTime);
			//Sleep(minDeltaTime * deltaTime * 1000);
			//Sleep(minDeltaTime - deltaTime - 0.001);
		}
		
		// sleep time is not precise, use loop to 'waste' extra cpu cycles
		while (deltaTime < minDeltaTime)
		{
			deltaTime = glfwGetTime() - previousTime;
		}

		float fps = 1.0 / deltaTime;
		std::cout << "FPS: " << fps << std::endl;

		/*
				// elapsed time since beginning
				elapsedTime = currentTime - initialTime;

				countedFrame += 1;

				// frame per second
				double fps = countedFrame / elapsedTime;

				// frameTime(deltaTime/elapsedTime)
				// 0.01s = 100
				// FPS (not average) = 1.0 / frameTime

				std::cout << "FPS: " << fps << std::endl;

				double frameTime = 1.0 / fps;
				// frameTime limit
				double frameTimeLimit = 1;
				// sleepDuration not accurate
				float sleepDuration = frameTimeLimit * frameTime * 1000;

				if (frameTime < frameTimeLimit)
				{
					Sleep(sleepDuration);
				}

				while (frameTime < frameTimeLimit)
				{
					// increase elapsed time but not counted frame
					// loop only breaks when extra time is elapsed and then continue to update the outer loop

					// elapsed time since beginning
					elapsedTime = glfwGetTime() - initialTime;

					fps = countedFrame / elapsedTime;
					frameTime = 1.0 / fps;
				}
		*/
#pragma endregion

// ==================================     Application    ==================================
#pragma region Application

		myApp.Update(deltaTime);

		myApp.Draw();
#pragma endregion

		
		//gameUpdate(deltaTime);

		//===============================

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		previousTime = currentTime;
	}




	glfwTerminate();
	return 0;
}