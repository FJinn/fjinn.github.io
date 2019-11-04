#ifndef _GAME_OF_LIFE_H
#define _GAME_OF_LIFE_H

#include "Bitmap.h"

#define TEXTURE_COUNT 7

GLuint mTextureID[TEXTURE_COUNT];

double xPos;
double yPos;

// largest = HEIGHT / 5, WIDTH / 5 = (width, height) = (600,600) = 360,000
// smallest = HEIGHT / 10, WIDTH / 10 = (300, 300) = 90,000
const float HEIGHT = 3000;
const float WIDTH = 3000;

double box_size = 10.0;
// 540, 1920 (width)
int map_height = HEIGHT / box_size;
int map_width = WIDTH / box_size;
int mapChangeSize = 50;
int oriMapHeight = HEIGHT / box_size;
int oriMapWidth = WIDTH / box_size;

float boardOffsetY = map_height * box_size;

// offset the board from the window
// use in mouse function to adjust by user 
// -x = move board to left, x = move board to right
float viewportOffsetX = 0;
// -y = move board to down, y = move board to up
float viewportOffsetY = 500.0;
float viewportMoveSpeed = 50.0f;

float buttonMinPosY = boardOffsetY + 0 + viewportOffsetY;
float buttonMaxPosY = boardOffsetY + 100 + viewportOffsetY;

// Start button position
float startMinPosX = 100;
float startMaxPosX = 300;
// CLear button position
float clearMinPosX = 500;
float clearMaxPosX = 700;
// Map button position
float mapMinPosX = 900;
float mapMaxPosX = 1100;
// time button position
float timeMinPosX = 1300;
float timeMaxPosX = 1500;

// Time rate for life update
int curTimeRate;
int oriTimeRate = 40;
int timeRateValueChanged;

bool* state;

bool startLife = false;

// bool for mouse drag
bool bMouseHold = false;

// texture int
int playNum = 0;
int speedNum = 0;

// pre declaration
void Display(GLFWwindow* window);
void LifeUpdate(int row, int column, bool state[]);

void loadTexture(const char* path, GLuint textureID)
{
	CBitmap bitmap(path);

	// Create Linear Filtered Texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // apply texture wrapping along horizontal part
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // apply texture wrapping along vertical part

	//// old school (minecraft) filtering
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // near filtering. (For when texture needs to scale up)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // far filtering. (For when texture needs to scale down)

	//bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near filtering. (For when texture needs to scale up)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far filtering. (For when texture needs to scale down)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
}

void Key_Callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	int widthTemp, heightTemp;
	glfwGetFramebufferSize(window, &widthTemp, &heightTemp);
	boardOffsetY = heightTemp - 100;

	buttonMinPosY = boardOffsetY + 0 + viewportOffsetY;
	buttonMaxPosY = boardOffsetY + 100 + viewportOffsetY;

	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS) && viewportOffsetY - viewportMoveSpeed > -HEIGHT + heightTemp +1000)
	{
		viewportOffsetY -= viewportMoveSpeed;
	}
	else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS) && HEIGHT + viewportOffsetY + viewportMoveSpeed < HEIGHT+ boardOffsetY)
	{
		viewportOffsetY += viewportMoveSpeed;
	}

	if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS) && viewportOffsetX + viewportMoveSpeed < 100)
	{
		viewportOffsetX += viewportMoveSpeed;
	}
	else if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS) && map_width*box_size - viewportOffsetX - viewportMoveSpeed < map_width*box_size)
	{
		viewportOffsetX -= viewportMoveSpeed;
	}

	buttonMinPosY = boardOffsetY + 300 + viewportOffsetY;
	buttonMaxPosY = boardOffsetY + 400 + viewportOffsetY;


	// Start button position
	startMinPosX = 100 - viewportOffsetX;
	startMaxPosX = 300 - viewportOffsetX;
	// CLear button position
	clearMinPosX = 500 - viewportOffsetX;
	clearMaxPosX = 700 - viewportOffsetX;
	// Map button position
	mapMinPosX = 900 - viewportOffsetX;
	mapMaxPosX = 1100 - viewportOffsetX;
	// Time button position
	timeMinPosX = 1300 - viewportOffsetX;
	timeMaxPosX = 1500 - viewportOffsetX;
}

void StartSimulation()
{
	startLife = !startLife;
}

void ClearMap()
{
	for (int j = 0; j<map_width; j++)
	{
		for (int i = 0; i<map_height; i++)
		{
			state[i + j * map_height] = false;
		}
	}
}

void ChangeMap()
{
	if (map_height == HEIGHT / 10)
	{
		box_size = 5;
		map_height = HEIGHT / box_size + 50;
		map_width = WIDTH/ box_size;
	}
	else if (map_height == HEIGHT / 5 + 50)
	{
		box_size = 10;
		map_height = HEIGHT / box_size;
		map_width = WIDTH / box_size;
	}

	state = new bool[map_height*map_width];
	for (int j = 0; j<map_width; j++)
	{
		for (int i = 0; i<map_height; i++)
		{
			state[i + j * map_height] = false;
		}
	}

	startLife = false;
}

void ChangeTimeRate()
{
	if (curTimeRate == oriTimeRate)
	{
		timeRateValueChanged = -20;
	}
	else if (curTimeRate < 20)
	{
		timeRateValueChanged = 20;
	}

	curTimeRate += timeRateValueChanged;
}

void OnMouseClick(GLFWwindow* window, int button, int mouse_state, int mods)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	
	int yPosition = yPos + viewportOffsetY;
	int xPosition = xPos - viewportOffsetX;

	int row = (map_height*box_size - yPosition) / box_size;
	int column = xPosition / box_size;

	if (button == GLFW_MOUSE_BUTTON_LEFT && mouse_state == GLFW_PRESS)
	{
		if (row >= 0 && column >= 0 && yPosition < buttonMinPosY - 100)
		{
			// turn mouse hold bool on
			bMouseHold = true;
		}
		else if (yPosition >= buttonMinPosY && yPosition <= buttonMaxPosY)
		{
			if (xPosition >= startMinPosX && xPosition <= startMaxPosX)
			{
				StartSimulation();
			}
			else if (xPosition >= clearMinPosX && xPosition <= clearMaxPosX)
			{
				ClearMap();
			}
			else if (xPosition >= mapMinPosX && xPosition <= mapMaxPosX)
			{
				ChangeMap();
			}
			else if (xPosition >= timeMinPosX && xPosition <= timeMaxPosX)
			{
				ChangeTimeRate();
			}
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && mouse_state == GLFW_RELEASE)
	{
		// turn bool mouse hold off
		bMouseHold = false;
	}

}

void MouseDrag(GLFWwindow* window)
{
	glfwGetCursorPos(window, &xPos, &yPos);

	static int previousRow;
	static int previousColumn;

	int yPosition = yPos + viewportOffsetY;
	int xPosition = xPos - viewportOffsetX;

	int row = (map_height*box_size - yPosition) / box_size;
	int maxRow = (map_height*box_size) / box_size;
	int column = xPosition / box_size;

	if (bMouseHold && row >= 0 && column >= 0 && row < maxRow && (previousRow != row || previousColumn != column) && yPosition < buttonMinPosY - 100)
	{
		glfwGetCursorPos(window, &xPos, &yPos);

		row = (map_height*box_size - yPosition) / box_size;
		column = xPosition / box_size;

		state[row + column * map_height] = !state[row + column * map_height];

		//Display(window);

		previousRow = row;
		previousColumn = column;
	}
}

void DrawUI(GLFWwindow* window)
{
	int widthTemp, heightTemp;
	glfwGetFramebufferSize(window, &widthTemp, &heightTemp);
	boardOffsetY = heightTemp -100;

	buttonMinPosY = boardOffsetY + 0 + viewportOffsetY;
	buttonMaxPosY = boardOffsetY + 100 + viewportOffsetY;


	if (startLife)
	{
		playNum = 1;
	}
	else
	{
		playNum = 0;
	}

	if (curTimeRate == 0)
	{
		speedNum = 4;
	}
	else if (curTimeRate == 20)
	{
		speedNum = 5;
	}
	else if (curTimeRate == 40)
	{
		speedNum = 6;
	}

	glEnable(GL_TEXTURE_2D); // enable texturing
	glBindTexture(GL_TEXTURE_2D, mTextureID[playNum]); // Bind panel texture

	glColor3f(1.0f, 1.0f, 1.0f);

	// Start
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(startMinPosX, buttonMinPosY);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(startMaxPosX, buttonMinPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(startMaxPosX, buttonMaxPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(startMaxPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, -1.0f); glVertex2f(startMinPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(startMinPosX, buttonMinPosY);

	glEnd();

	// Clear
	glBindTexture(GL_TEXTURE_2D, mTextureID[2]); // Bind panel texture
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(clearMinPosX, buttonMinPosY);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(clearMaxPosX, buttonMinPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(clearMaxPosX, buttonMaxPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(clearMaxPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, -1.0f); glVertex2f(clearMinPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(clearMinPosX, buttonMinPosY);

	glEnd();

	// Map
	glBindTexture(GL_TEXTURE_2D, mTextureID[3]); // Bind panel texture
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(mapMinPosX, buttonMinPosY);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(mapMaxPosX, buttonMinPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(mapMaxPosX, buttonMaxPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(mapMaxPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, -1.0f); glVertex2f(mapMinPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(mapMinPosX, buttonMinPosY);

	glEnd();

	// Time
	glBindTexture(GL_TEXTURE_2D, mTextureID[speedNum]); // Bind panel texture
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(timeMinPosX, buttonMinPosY);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(timeMaxPosX, buttonMinPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(timeMaxPosX, buttonMaxPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(timeMaxPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, -1.0f); glVertex2f(timeMinPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(timeMinPosX, buttonMinPosY);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void init()
{
	state = new bool[map_height*map_width];
	for (int j=0; j<map_width; j++)
	{
		for (int i=0; i<map_height; i++)
		{
			state[i + j * map_height] = false;
		}
	}

	curTimeRate = oriTimeRate;

	// openGL generate texture id 
	glGenTextures(TEXTURE_COUNT, mTextureID);
	loadTexture("../media/Start.bmp", mTextureID[0]);
	loadTexture("../media/Paused.bmp", mTextureID[1]);
	loadTexture("../media/Clear.bmp", mTextureID[2]);
	loadTexture("../media/Map.bmp", mTextureID[3]);
	loadTexture("../media/0.bmp", mTextureID[4]);
	loadTexture("../media/20.bmp", mTextureID[5]);
	loadTexture("../media/40.bmp", mTextureID[6]);

}

void deinit()
{
	delete [] state;
}

// draw box
void DrawBox(int i, int j, bool alive, GLFWwindow* window)
{

	int widthTemp, heightTemp;
	glfwGetFramebufferSize(window, &widthTemp, &heightTemp);
	boardOffsetY = heightTemp - 100;

	buttonMinPosY = boardOffsetY + 0 + viewportOffsetY;
	buttonMaxPosY = boardOffsetY + 100 + viewportOffsetY;


	float p[2];
	GLfloat a;
	GLfloat b;
	GLfloat c;

	GLfloat bg[3] = { 0.1, 0.1, 0.1 };
	GLfloat life[3] = { 0.0, 1.0, 0.5 };

	if (alive)
	{
		glColor3fv(life);
	}
	else
	{
		glColor3fv(bg);
	}

	c = box_size;
	// x coordinate
	a = j * c;
	// y coordinate
	b = (map_height - 1 - i) * c;

	// box fill offset
	static double temp = 0;

	buttonMinPosY = buttonMinPosY - 100;

	if (b <= buttonMinPosY)
	{
		//
		//  Fill boxes with bg or life.
		//
		glBegin(GL_POLYGON);
		p[0] = a + temp;
		p[1] = b + temp;
		glVertex2fv(p);
		p[0] = a + c - temp;
		p[1] = b + temp;
		glVertex2fv(p);
		p[0] = a + c - temp;
		p[1] = b + c - temp;
		glVertex2fv(p);
		p[0] = a + temp;
		p[1] = b + c - temp;
		glVertex2fv(p);
		glEnd();
		//
		//  Draw box boundaries in BLUE.
		//
		glColor3f(0.0, 0.0, 0.7);

		glBegin(GL_LINE_LOOP);
		p[0] = a;
		p[1] = b;
		glVertex2fv(p);
		p[0] = a + c;
		p[1] = b;
		glVertex2fv(p);
		p[0] = a + c;
		p[1] = b + c;
		glVertex2fv(p);
		p[0] = a;
		p[1] = b + c;
		glVertex2fv(p);
		glEnd();
	}
	
}
void Display(GLFWwindow* window)
{
	//
	//  Clear the window.
	//
	glClear(GL_COLOR_BUFFER_BIT);
	//
	//  Draw each box.
	//

	for (int j = 0; j < map_width; j++)
	{
		for (int i = 0; i < map_height; i++)
		{
			DrawBox(i, j, state[i + j * map_height], window);
		}
	}

	DrawUI(window);
}

void LifeUpdate(int row, int column, bool state[])
{
	int neighbors;

	bool *tempState;

	tempState = new bool[row*column];

	for (int j = 0; j < column; j++)
	{
		for (int i = 0; i < row; i++)
		{
			neighbors = 0;
			if (0 < i && 0 < j)
			{
				// top left
				neighbors = neighbors + (int)state[(i - 1) + (j - 1)*row];
			}
			if (0 < i)
			{
				// top
				neighbors = neighbors + (int)state[(i - 1) + (j)*row];
			}
			if (0 < i && j < column - 1)
			{
				// top right
				neighbors = neighbors + (int)state[(i - 1) + (j + 1)*row];
			}
			if (0 < j)
			{
				// left
				neighbors = neighbors + (int)state[(i)+(j - 1)*row];
			}
			if (j < column - 1)
			{
				// right
				neighbors = neighbors + (int)state[(i)+(j + 1)*row];
			}
			if (i < row - 1 && 0 < j)
			{
				// bottom left
				neighbors = neighbors + (int)state[(i + 1) + (j - 1)*row];
			}
			if (i < row - 1)
			{
				// bottom
				neighbors = neighbors + (int)state[(i + 1) + (j)*row];
			}
			if (i < row - 1 && j < column - 1)
			{
				// bottom right
				neighbors = neighbors + (int)state[(i + 1) + (j + 1)*row];
			}

			if (neighbors == 3)
			{
				tempState[i + j * row] = true;
			}
			else if (neighbors == 2)
			{
				tempState[i + j * row] = state[i + j * row];
			}
			else
			{
				tempState[i + j * row] = false;
			}
		}
	}
	//
	//  Update.
	//
	for (int j = 0; j < column; j++)
	{
		for (int i = 0; i < row; i++)
		{
			state[i + j * row] = tempState[i + j * row];
		}
	}

	delete []tempState;
}

#endif
