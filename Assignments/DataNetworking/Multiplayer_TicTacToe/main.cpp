#include <iostream>

#include "MyPhoton.h"

#include <windows.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>

#include "Application.h"

using namespace std;

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;

#define TEXTURE_COUNT 6
GLuint GtextureID[TEXTURE_COUNT];

void onWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//! Use ortho2D view
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		glfwGetCursorPos(window, &xpos, &ypos);

		MyPhoton::getInstance().SetMousePosition(xpos, ypos);
		MyPhoton::getInstance().sendMyData();
	}
		
}

void UpdateMousePosition(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xpos, &ypos);

	MyPhoton::getInstance().SetMousePosition(xpos, ypos);
	MyPhoton::getInstance().sendMyData();
}
*/

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);

		MyPhoton::getInstance().SetMousePosition(xpos, ypos);

	}
}

//=======================================================================================================
// game engine

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

void init(void)
{
	glGenTextures(TEXTURE_COUNT, GtextureID);
	loadTexture("../Media/tree.bmp", GtextureID[0]);
}
//=======================================================================================================

int main (void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create m_a windowed mode window and its OpenGL context */
	window = glfwCreateWindow (RESOLUTION_X, RESOLUTION_Y, "", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback (window, onWindowResized);
	
	//glfwSetKeyCallback(window, key_callback);

	glfwSetMouseButtonCallback(window, mouse_button_callback);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized (window, RESOLUTION_X, RESOLUTION_Y);

	glfwSwapInterval(1); //enable/disable vsync

	// ==================================     Application    ==================================
	Application myApp;
	myApp.Start();

	// ================================== FPS and Delta Time ==================================

	// cache previous time
	double previousTime = glfwGetTime();
	double maxFPS = 60;
	double minDeltaTime = 1.0 / maxFPS;

	//===================================================================================================

	MyPhoton::getInstance().connect();

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

#pragma endregion

		// ==================================     Application    ==================================
#pragma region Application

		myApp.Update(deltaTime);

		myApp.Draw();
#pragma endregion


		//UpdateMousePosition(window);

		//MyPhoton::getInstance().run();

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwTerminate();
	return 0;
}