#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "PathFindingAlgorithm.h"
#include "Bitmap.h"

#define TEXTURE_COUNT 11

GLuint mTextureID[TEXTURE_COUNT];

double xPos;
double yPos;

const float HEIGHT = 700;
const float WIDTH = 1800;

double box_size = 20.0;
// 540, 1920 (width)
int map_height = HEIGHT / box_size;
int map_width = WIDTH / box_size;

float boardOffsetY = map_height * box_size;

// offset the board from the window
// use in mouse function to adjust by user 
// -x = move board to left, x = move board to right
float viewportOffsetX = 50;
// -y = move board to down, y = move board to up
float viewportOffsetY = -50; // 500.0;
float viewportMoveSpeed = 0; // 50.0f;

float buttonMinPosY = boardOffsetY + 0 + viewportOffsetY;
float buttonMaxPosY = boardOffsetY + 100 + viewportOffsetY;

// Start button position
float startMinPosX = 100;
float startMaxPosX = 300;
// CLear button position
float clearMinPosX = 500;
float clearMaxPosX = 700;
// Map button position
// map in game of life
// diagonal option in pathfinding
float mapMinPosX = 900;
float mapMaxPosX = 1100;
// time button position
// time in game of life
// strategy option in pathfinding
float timeMinPosX = 1300;
float timeMaxPosX = 1500;
// weight changing for AStar
float weightMinPosX = 1600;
float weightMaxPosX = 1800;

// bool for mouse drag
bool bMouseHold = false;

//=============================================================================================================
// Path Finding Variables
// pointers to each box
BoxStatus* boxStatus[40 * 90];

//=============================================================================================================
// int to control 
int startNum = 0;
int weightNum = 0;
int tempNum = 1;
// 5 is dijkstra, 6 is AStar
int strategyNum = 5;
// bool to check if strategy has changed
bool changedStrategy = false;
// int to control changing start position and target position
// 0 = nothing happens, 1 = START has been selected, 2 = TARGET has been selected
int MovingBoxState = 0;

//=============================================================================================================

// pre declaration
void Display(GLFWwindow* window);

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

	/*
	if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS) && viewportOffsetY - viewportMoveSpeed > -HEIGHT + heightTemp + 1000)
	{
		viewportOffsetY -= viewportMoveSpeed;
	}
	else if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS) && HEIGHT + viewportOffsetY + viewportMoveSpeed < HEIGHT + boardOffsetY)
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
	*/

	buttonMinPosY = boardOffsetY + 300 + viewportOffsetY;
	buttonMaxPosY = boardOffsetY + 400 + viewportOffsetY;


	// Start button position
	startMinPosX = 100;// - viewportOffsetX;
	startMaxPosX = 300;//  - viewportOffsetX;
	// CLear button position
	clearMinPosX = 500;//  - viewportOffsetX;
	clearMaxPosX = 700;//  - viewportOffsetX;
	// Map button position
	mapMinPosX = 900;//  - viewportOffsetX;
	mapMaxPosX = 1100;//  - viewportOffsetX;
	// Time button position
	timeMinPosX = 1300;//  - viewportOffsetX;
	timeMaxPosX = 1500;//  - viewportOffsetX;
	// weight button position
	weightMinPosX = 1600;
	weightMaxPosX = 1800;

}

void StartSimulation()
{
	// start/pause/resume, if = true, means start/resume, else false, pause
	findStart = !findStart;

	if (findStart == true)
	{
		startNum = 1;
	}
	else
	{
		startNum = 0;
	}
}

void ClearWall()
{
	findStart = false;

	for (int j = 0; j < map_width; j++)
	{
		for (int i = 0; i < map_height; i++)
		{
			if (boxStatus[i + j * map_height]->state == WALL || boxStatus[i + j * map_height]->state == DONE
				|| boxStatus[i + j * map_height]->state == PATH)
			{
				boxStatus[i + j * map_height]->state = BLANK;
			}

			if (boxStatus[i + j * map_height]->myDistance != 0)
			{
				boxStatus[i + j * map_height]->myDistance = INT_MAX;
			}

			boxStatus[i + j * map_height]->isPicked = false;
		}
	}
	// set currentBox points to null
	isReset = true;
}

void DiagonalOption()
{
	// only when it is not finding path, incase it breaks the algorithm
	if (findStart == false)
	{
		if (diagonalNum == 3)
		{
			diagonalNum = 4;
		}
		else if (diagonalNum == 4)
		{
			diagonalNum = 3;
		}
	}
}

void StrategyOption()
{
	// only when it is not finding path, incase it breaks the algorithm
	if (findStart == false)
	{
		if (strategyNum == 5)
		{
			strategyNum = 6;
			changedStrategy = true;
		}
		else if (strategyNum == 6)
		{
			strategyNum = 5;
			changedStrategy = true;
		}
	}
}

void WeightOption()
{
	if (weightNum <= 0)
	{
		tempNum = 1;
	}
	else if (weightNum >= 3)
	{
		tempNum = -1;
	}
	weightNum += tempNum;

	if (weightNum == 0)
	{
		weight = 1;
	}
	else if (weightNum == 1)
	{
		weight = 5;
	}
	else if (weightNum == 2)
	{
		weight = 10;
	}
	else if (weightNum == 3)
	{
		weight = 20;
	}
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

			if (boxStatus[row + column * map_height]->state == START && MovingBoxState == 0)
			{
				boxStatus[row + column * map_height]->state = BLANK;
				boxStatus[row + column * map_height]->myDistance = INT_MAX;
				MovingBoxState = 1;
			}
			else if (boxStatus[row + column * map_height]->state == TARGET && MovingBoxState == 0)
			{
				boxStatus[row + column * map_height]->state = BLANK;
				MovingBoxState = 2;
			}
		}
		else if (yPosition >= buttonMinPosY && yPosition <= buttonMaxPosY)
		{
			if (xPosition >= startMinPosX && xPosition <= startMaxPosX)
			{
				StartSimulation();
			}
			else if (xPosition >= clearMinPosX && xPosition <= clearMaxPosX)
			{
				ClearWall();
			}
			else if (xPosition >= mapMinPosX && xPosition <= mapMaxPosX)
			{
				DiagonalOption();
			}
			else if (xPosition >= timeMinPosX && xPosition <= timeMaxPosX)
			{
				StrategyOption();
			}
			else if (xPosition >= weightMinPosX && xPosition <= weightMaxPosX)
			{
				WeightOption();
			}
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && mouse_state == GLFW_RELEASE)
	{
		// turn bool mouse hold off
		bMouseHold = false;

		if (boxStatus[row + column * map_height]->state == BLANK && MovingBoxState == 1)
		{
			boxStatus[row + column * map_height]->state = START;
			boxStatus[row + column * map_height]->myDistance = 0;
			MovingBoxState = 0;
		}
		else if (boxStatus[row + column * map_height]->state == BLANK && MovingBoxState == 2)
		{
			boxStatus[row + column * map_height]->state = TARGET;
			MovingBoxState = 0;
		}
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

	if (bMouseHold && row >= 0 && column >= 0 && row < maxRow && (previousRow != row || previousColumn != column) && yPosition < buttonMinPosY - 100
		&& MovingBoxState == 0)
	{
		glfwGetCursorPos(window, &xPos, &yPos);

		row = (map_height*box_size - yPosition) / box_size;
		column = xPosition / box_size;

		if (boxStatus[row + column * map_height]->state == WALL)
		{
			boxStatus[row + column * map_height]->state = BLANK;
		}
		else if (boxStatus[row + column * map_height]->state == BLANK)
		{
			boxStatus[row + column * map_height]->state = WALL;
		}

		previousRow = row;
		previousColumn = column;
	}
}

void DrawUI(GLFWwindow* window)
{
	//==========================================================================
	
	int widthTemp, heightTemp;
	glfwGetFramebufferSize(window, &widthTemp, &heightTemp);
	boardOffsetY = heightTemp - 100;

	buttonMinPosY = boardOffsetY + 0 + viewportOffsetY;
	buttonMaxPosY = boardOffsetY + 100 + viewportOffsetY;

	glEnable(GL_TEXTURE_2D); // enable texturing
	glBindTexture(GL_TEXTURE_2D, mTextureID[startNum]); // Bind panel texture

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

	// Diagonal
	glBindTexture(GL_TEXTURE_2D, mTextureID[diagonalNum]); // Bind panel texture
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(mapMinPosX, buttonMinPosY);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(mapMaxPosX, buttonMinPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(mapMaxPosX, buttonMaxPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(mapMaxPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, -1.0f); glVertex2f(mapMinPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(mapMinPosX, buttonMinPosY);

	glEnd();

	// Strategy
	glBindTexture(GL_TEXTURE_2D, mTextureID[strategyNum]); // Bind panel texture
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(timeMinPosX, buttonMinPosY);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(timeMaxPosX, buttonMinPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(timeMaxPosX, buttonMaxPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(timeMaxPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, -1.0f); glVertex2f(timeMinPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(timeMinPosX, buttonMinPosY);

	glEnd();

	// Weight
	glBindTexture(GL_TEXTURE_2D, mTextureID[weightNum + 7]); // Bind panel texture
	glBegin(GL_TRIANGLES);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(weightMinPosX, buttonMinPosY);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(weightMaxPosX, buttonMinPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(weightMaxPosX, buttonMaxPosY);
	glTexCoord2f(1.0f, -1.0f); glVertex2f(weightMaxPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, -1.0f); glVertex2f(weightMinPosX, buttonMaxPosY);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(weightMinPosX, buttonMinPosY);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void init()
{
	for (int j = 0; j < map_width; j++)
	{
		for (int i = 0; i < map_height; i++)
		{
			boxStatus[i + j * map_height] = new BoxStatus();
			// Initialize all distances as INFINITE and state as blank 
			boxStatus[i + j * map_height]->state = BLANK;
			boxStatus[i + j * map_height]->myDistance = INT_MAX;
			boxStatus[i + j * map_height]->isPicked = false;
			boxStatus[i + j * map_height]->myRow = i;
			boxStatus[i + j * map_height]->myColumn = j;
			boxStatus[i + j * map_height]->fCost = INT_MAX;
		}
	}
	// initialize start point
	// 0 bottom left, 1 = going up, one column = 40 (height/box_size)
	boxStatus[790]->state = START;
	boxStatus[790]->myDistance = 0;

	boxStatus[1770]->state = TARGET;

	// openGL generate texture id 
	glGenTextures(TEXTURE_COUNT, mTextureID);
	loadTexture("../media/Start.bmp", mTextureID[0]);
	loadTexture("../media/Paused.bmp", mTextureID[1]);
	loadTexture("../media/Clear.bmp", mTextureID[2]);
	loadTexture("../media/NonDiagonal.bmp", mTextureID[3]);
	loadTexture("../media/Diagonal.bmp", mTextureID[4]);
	loadTexture("../media/Dijkstra.bmp", mTextureID[5]);
	loadTexture("../media/AStar.bmp", mTextureID[6]);
	loadTexture("../media/Weight1.bmp", mTextureID[7]);
	loadTexture("../media/Weight5.bmp", mTextureID[8]);
	loadTexture("../media/Weight10.bmp", mTextureID[9]);
	loadTexture("../media/Weight20.bmp", mTextureID[10]);

}

void deinit()
{
	for (int j = 0; j < map_width; j++)
	{
		for (int i = 0; i < map_height; i++)
		{
			delete boxStatus[i + j * map_height];
		}
	}
}

// draw box
void DrawBox(int i, int j, BoxState bs, GLFWwindow* window, int distance)
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

	GLfloat blankColor[3] = { 0.1, 0.1, 0.1 };
	GLfloat wallColor[3] = { 1.0, 1.0, 0.0 };
	GLfloat startColor[3] = { 0.0, 1.0, 0.5};
	GLfloat targetColor[3] = { 1.0, 0.0, 0.5 };
	GLfloat pathColor[3] = { 0.0, 0.2, 1.0 };
	GLfloat doneColor[3] = { 1.0, 1.0, 1.0 };

	if (bs == WALL)
	{
		glColor3fv(wallColor);
	}
	else if (bs == BLANK)
	{
		glColor3fv(blankColor);
	}
	else if (bs == START)
	{
		glColor3fv(startColor);
	}
	else if (bs == TARGET)
	{
		glColor3fv(targetColor);
	}
	else if (bs == PATH)
	{
		glColor3fv(pathColor);
	}
	else if (bs == DONE)
	{
		glColor3fv(doneColor);
	}

	c = box_size;
	// x coordinate
	a = j * c;
	// y coordinate
	b = (map_height - 1 - i) * c;

	// box fill offset
	static double temp = 0;

	buttonMinPosY = buttonMinPosY - 100;

//	if (b <= buttonMinPosY)
//	{
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
		glColor3f(0.0, 0.0, 0.6);

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
//	}

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
			DrawBox(i, j, boxStatus[i + j * map_height]->state, window, boxStatus[i + j * map_height]->myDistance);
		}
	}

	DrawUI(window);
}

#endif
