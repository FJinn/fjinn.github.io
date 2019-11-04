#include <iostream>
#include <ctime>
#include "windows.h"
#include <cmath>
#include <limits>
#include <vector>
#include "conio_yp.h"
#include <string>
#include "highscore.h"

using namespace std;

enum DIRECTION
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST,
	NONE,
	TOTAL_DIRECTION
};

enum GRID_TYPE
{
	SOURCE = 0,
	TARGET,
	EMPTY,
	STRAIGHT_HORIZONTAL,
	STRAIGHT_VERTICAL,
	LSHAPE_0_DEGREE,
	LSHAPE_90_DEGREE,
	LSHAPE_180_DEGREE,
	LSHAPE_270_DEGREE,
	TSHAPE_0_DEGREE,
	TSHAPE_90_DEGREE,
	TSHAPE_180_DEGREE,
	TSHAPE_270_DEGREE,
	BLOCK,
	DOT,
	TOTAL_TYPE
};

struct Node
{
	GRID_TYPE type;
	char **sprite;
	int color;
	int colorOriginal;
	int RotateCounter = 0;
	//! 4 pointers
	Node* northNode;
	Node* southNode;
	Node* eastNode;
	Node* westNode;

	bool isNorthNodeConnectable;
	bool isSouthNodeConnectable;
	bool isEastNodeConnectable;
	bool isWestNodeConnectable;


	void Initialize(GRID_TYPE type);
	void SetType(GRID_TYPE type);
	void CopySprite(char tempSprite[][3]);
};

void Node::Initialize(GRID_TYPE type)
{
	for(int i=0; i<3; i++)
	{
		sprite = new char* [3];
		for(int j=0; j<3; j++)
		{
			sprite[j] = new char[3];
		}
	}
	SetType(type);
	colorOriginal = color;
}

void Node::SetType(GRID_TYPE type) //!sprite design
{
	this->type = type;

	northNode = NULL;
	southNode = NULL;
	eastNode = NULL;
	westNode = NULL;

	if(type == SOURCE)
	{
		color = YELLOW;

		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{'#', '#', '#'},
			{'#', '#', '#'},
			{'#', '#', '#'}
		};
		CopySprite(tempSprite);
	}
	else if(type == TARGET)
	{
		color = CYAN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{'#', '#', '#'},
			{'#', '#', '#'},
			{'#', '#', '#'}
		};
		CopySprite(tempSprite);
	}
	else if(type == EMPTY)
	{
		color = GREEN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = false;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] =
		{
			{' ', ' ', ' '},
			{' ', ' ', ' '},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == STRAIGHT_VERTICAL)
	{
		color = CYAN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = false;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] =
		{
			{' ', '#', ' '},
			{' ', '#', ' '},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == STRAIGHT_HORIZONTAL)
	{
		color = CYAN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{' ', ' ', ' '},
			{'#', '#', '#'},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_0_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = true;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] =
		{
			{' ', '#', ' '},
			{' ', '#', '#'},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_90_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] =
		{
			{' ', ' ', ' '},
			{' ', '#', '#'},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_180_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = false;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{' ', ' ', ' '},
			{'#', '#', ' '},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == LSHAPE_270_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = false;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{' ', '#', ' '},
			{'#', '#', ' '},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_0_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{' ', ' ', ' '},
			{'#', '#', '#'},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_90_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = false;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{' ', '#', ' '},
			{'#', '#', ' '},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_180_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{' ', '#', ' '},
			{'#', '#', '#'},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == TSHAPE_270_DEGREE)
	{
		color = CYAN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] =
		{
			{' ', '#', ' '},
			{' ', '#', '#'},
			{' ', '#', ' '}
		};
		CopySprite(tempSprite);
	}
	else if(type == BLOCK)
	{
		color = CYAN;
		
		isNorthNodeConnectable = false;
		isSouthNodeConnectable = false;
		isEastNodeConnectable = false;
		isWestNodeConnectable = false;
		
		char tempSprite[3][3] =
		{
			{'#', ' ', '#'},
			{' ', ' ', ' '},
			{'#', ' ', '#'}
		};
		CopySprite(tempSprite);
	}
	else if(type == DOT)
	{
		color = CYAN;
		
		isNorthNodeConnectable = true;
		isSouthNodeConnectable = true;
		isEastNodeConnectable = true;
		isWestNodeConnectable = true;
		
		char tempSprite[3][3] =
		{
			{' ', ' ', ' '},
			{' ', '#', ' '},
			{' ', ' ', ' '}
		};
		CopySprite(tempSprite);
	}
}

void Node::CopySprite(char tempSprite[][3])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			sprite[i][j] = tempSprite[i][j];
		}
	}
}

Node** gridNode;
int totalRow = 0;
int totalCol = 0;
int sourceRow = 0;
int sourceCol = 0;
bool isSolve = false;
int targetCounter = 0;
int mode = 1; // difficulty level
bool isExit = false;
bool isEsc = false; // for leaving game without solving it
int tempType = 0;  // for randomization and insert grid type
int targetNumber = 0; // how many target in the game
int steps = 0; // for scoring

void MarkLink(Node* node, DIRECTION direction)
{
	node->color = YELLOW;
	//! north node
	if(node->northNode != NULL && direction != NORTH)
	{
		if(node->northNode->color != YELLOW)
		{
			MarkLink(node->northNode, SOUTH);
		}
	}
	//! southNode pointer
	if(node->southNode != NULL && direction != SOUTH)
	{
		if(node->southNode->color != YELLOW)
		{
			MarkLink(node->southNode, NORTH);
		}	
	}
	//! eastNode pointer
	if(node->eastNode != NULL && direction != EAST)
	{
		if(node->eastNode->color != YELLOW)
		{
			MarkLink(node->eastNode, WEST);
		}
	}
	//! westNode pointer
	if(node->westNode != NULL && direction != WEST)
	{
		if(node->westNode->color != YELLOW)
		{
			MarkLink(node->westNode, EAST);	
		}
	}
}

void Unlink()
{
	for(int i=0; i<totalRow; i++)
	{
		for(int j=0; j<totalCol; j++)
		{
			gridNode[i][j].color = gridNode[i][j].colorOriginal;
			gridNode[i][j].northNode = NULL;
			gridNode[i][j].southNode = NULL;
			gridNode[i][j].eastNode = NULL;
			gridNode[i][j].westNode = NULL;
		}
	}
}

bool ParseLink()
{
	bool isAllConnected = true;
	Node* currentNode = &gridNode[sourceRow][sourceCol];
	
	MarkLink(currentNode, NONE);
	
	//! check ->determine the all source are connected to the target
	//! check if all target are in yellow
	
	for(int i=0; i<totalRow; i++)
	{
		for(int j=0; j<totalCol; j++)
		{
			if(gridNode[i][j].type == TARGET)
			{
				if(gridNode[i][j].color == YELLOW)
				{
					targetCounter++;
				}
			}
		}
	}
	
	if(mode == 1)
	{
		targetNumber = 3;
	}
	else
	{
		targetNumber = 4;
	}
	
	if(targetCounter >= targetNumber)
	{
		isAllConnected = true;
	}	
	else 
	{
		targetCounter = 0; // reset the counter so the game will not end before all target turn to yellow
		isAllConnected = false;
	}	
	
	return isAllConnected;
}

void ReinitializeLink()
{
	for(int i=0; i<totalRow; i++)
	{
		for(int j=0; j<totalCol; j++)
		{
			//! check north neighbour
			if(i>0)
			{
				if(gridNode[i][j].isNorthNodeConnectable == true && gridNode[i-1][j].isSouthNodeConnectable == true)
				{
					gridNode[i][j].northNode = &gridNode[i-1][j];
				}
			}
			//!check south neighbour
			if(i<totalRow-1)
			{
				if(gridNode[i+1][j].isNorthNodeConnectable == true && gridNode[i][j].isSouthNodeConnectable == true)
				{
					gridNode[i][j].southNode = &gridNode[i+1][j];
				}
			}
			//!check east neighbour
			if(j<totalCol-1)
			{
				if(gridNode[i][j].isEastNodeConnectable == true && gridNode[i][j+1].isWestNodeConnectable == true)
				{
					gridNode[i][j].eastNode = &gridNode[i][j+1];
				}
			}
			//!check west neighbour
			if(j>0)
			{
				if(gridNode[i][j-1].isEastNodeConnectable == true && gridNode[i][j].isWestNodeConnectable == true)
				{
					gridNode[i][j].westNode = &gridNode[i][j-1];
				}
			}
		}
	}
}

void InitializeGrid() //! maze or map design
{
	totalRow = 6;
	totalCol = 9;
	if(mode == 1)
	{
		GRID_TYPE tempGrid[totalRow][totalCol] =	
		{
			{TARGET, TSHAPE_0_DEGREE, LSHAPE_270_DEGREE, EMPTY, EMPTY, EMPTY, LSHAPE_270_DEGREE, STRAIGHT_HORIZONTAL, TARGET},
			{EMPTY, EMPTY, STRAIGHT_HORIZONTAL, LSHAPE_270_DEGREE, LSHAPE_0_DEGREE, EMPTY, TSHAPE_0_DEGREE, EMPTY, EMPTY},
			{EMPTY, LSHAPE_270_DEGREE, TSHAPE_0_DEGREE, TSHAPE_0_DEGREE, TSHAPE_0_DEGREE, TSHAPE_0_DEGREE, TSHAPE_0_DEGREE, EMPTY, EMPTY},
			{EMPTY, TSHAPE_0_DEGREE, LSHAPE_270_DEGREE, LSHAPE_270_DEGREE, EMPTY, LSHAPE_270_DEGREE, STRAIGHT_HORIZONTAL, LSHAPE_270_DEGREE, EMPTY},
			{EMPTY, TSHAPE_0_DEGREE, LSHAPE_270_DEGREE, STRAIGHT_HORIZONTAL, TSHAPE_0_DEGREE, LSHAPE_270_DEGREE, LSHAPE_270_DEGREE, LSHAPE_270_DEGREE, TARGET},
			{EMPTY, LSHAPE_270_DEGREE, LSHAPE_270_DEGREE, EMPTY, SOURCE, EMPTY, EMPTY, EMPTY, EMPTY}
		};	

		gridNode = new Node*[totalRow];
		for(int i=0; i<totalRow; i++)
		{
			gridNode[i] = new Node[totalCol];
			for(int j=0; j<totalCol; j++)
			{
				Node tempNode;
				tempNode.Initialize(tempGrid[i][j]);
				//! keep track the source x and y location
				
				if(tempGrid[i][j] == SOURCE)
				{
					sourceRow = i;
					sourceCol = j;
				}
				gridNode[i][j] = tempNode;
			}
		}
	}
	else if(mode == 2)
	{
		GRID_TYPE tempGrid[totalRow][totalCol] =	
		{
			{TARGET, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, TARGET},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{TARGET, EMPTY, EMPTY, EMPTY, SOURCE, EMPTY, EMPTY, EMPTY, TARGET}
		};	

		gridNode = new Node*[totalRow];
		for(int i=0; i<totalRow; i++)
		{
			gridNode[i] = new Node[totalCol];
			for(int j=0; j<totalCol; j++)
			{
				Node tempNode;
				tempNode.Initialize(tempGrid[i][j]);
				//! keep track the source x and y location
				
				if(tempGrid[i][j] == SOURCE)
				{
					sourceRow = i;
					sourceCol = j;
				}
				gridNode[i][j] = tempNode;
			}
		}	
		tempType = rand()%12 +1;
	}
	else if(mode == 3)
	{
		GRID_TYPE tempGrid[totalRow][totalCol] =	
		{
			{TARGET, EMPTY, LSHAPE_270_DEGREE, EMPTY, EMPTY, EMPTY, LSHAPE_180_DEGREE, EMPTY, TARGET},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
			{TARGET, EMPTY, LSHAPE_0_DEGREE, EMPTY, SOURCE, EMPTY, LSHAPE_90_DEGREE, EMPTY, TARGET}
		};	

		gridNode = new Node*[totalRow];
		for(int i=0; i<totalRow; i++)
		{
			gridNode[i] = new Node[totalCol];
			for(int j=0; j<totalCol; j++)
			{
				Node tempNode;
				tempNode.Initialize(tempGrid[i][j]);
				//! keep track the source x and y location
				
				if(tempGrid[i][j] == SOURCE)
				{
					sourceRow = i;
					sourceCol = j;
				}
				gridNode[i][j] = tempNode;
			}
		}	
		tempType = rand()%12 +1;
	}
	
	ParseLink();
}

int tempI = 3; // for ypos
int tempJ = 4; // for xpos
int LY = 3*3+1+3+2;
int LX = 2*4+3+4+1;

void Move()
{
	if(GetAsyncKeyState(VK_LEFT))
	{
		if(tempJ != 0)
		{
			tempJ--;
		}
		
		LX = 2*tempJ+3+tempJ+1;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		if(tempJ != totalCol-1)
		{
			tempJ++;
		}
		
		LX = 2*tempJ+3+tempJ+1;
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		if(tempI != 0)
		{
			tempI--;
		}
		
		LY = 3*tempI+1+tempI+2;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		if(tempI != totalRow-1)
		{
			tempI++;
		}
		
		LY = 3*tempI+1+tempI+2;
	}
}

void DisplayType() // for normal and hard mode display 
{
	gotoxy(10, 32);
	if(tempType == 1)
	{	
		cout << "STRAIGHT VERTICAL";
		gotoxy(15, 33);
		cout << " # ";
		gotoxy(15, 34);
		cout << " # ";
		gotoxy(15, 35);
		cout << " # ";
	}
	else if(tempType == 2)
	{
		cout << "STRAIGHT HORIZONTAL";
		gotoxy(15, 33);
		cout << "   ";
		gotoxy(15, 34);
		cout << "###";
		gotoxy(15, 35);
		cout << "   ";
	}
	else if(tempType == 3)
	{
		cout << "LSHAPE 90 DEGREE";
		gotoxy(15, 33);
		cout << "   ";
		gotoxy(15, 34);
		cout << " ##";
		gotoxy(15, 35);
		cout << " # ";
	}
	else if(tempType == 4)
	{
		cout << "LSHAPE 180 DEGREE";
		gotoxy(15, 33);
		cout << "   ";
		gotoxy(15, 34);
		cout << "## ";
		gotoxy(15, 35);
		cout << " # ";
	}
	else if(tempType == 5)
	{
		cout << "LSHAPE 270 DEGREE";
		gotoxy(15, 33);
		cout << " # ";
		gotoxy(15, 34);
		cout << "## ";
		gotoxy(15, 35);
		cout << "   ";
	}
	else if(tempType == 6)
	{
		cout << "LSHAPE 0 DEGREE";
		gotoxy(15, 33);
		cout << " # ";
		gotoxy(15, 34);
		cout << " ##";
		gotoxy(15, 35);
		cout << "   ";
	}
	else if(tempType == 7)
	{
		cout << "TSHAPE 90 DEGREE";
		gotoxy(15, 33);
		cout << " # ";
		gotoxy(15, 34);
		cout << "## ";
		gotoxy(15, 35);
		cout << " # ";
	}
	else if(tempType == 8)
	{
		cout << "TSHAPE 180 DEGREE";
		gotoxy(15, 33);
		cout << " # ";
		gotoxy(15, 34);
		cout << "###";
		gotoxy(15, 35);
		cout << "   ";
	}
	else if(tempType == 9)
	{
		cout << "TSHAPE 270 DEGREE";
		gotoxy(15, 33);
		cout << " # ";
		gotoxy(15, 34);
		cout << " ##";
		gotoxy(15, 35);
		cout << " # ";
	}
	else if(tempType == 10)
	{
		cout << "TSHAPE 0 DEGREE";
		gotoxy(15, 33);
		cout << "   ";
		gotoxy(15, 34);
		cout << "###";
		gotoxy(15, 35);
		cout << " # ";
	}
	else if(tempType == 11)
	{
		cout << "BLOCK";
		gotoxy(15, 33);
		cout << "# #";
		gotoxy(15, 34);
		cout << "   ";
		gotoxy(15, 35);
		cout << "# #";
	}
	else if(tempType == 12)
	{
		cout << "DOT";
		gotoxy(15, 33);
		cout << "   ";
		gotoxy(15, 34);
		cout << " # ";
		gotoxy(15, 35);
		cout << "   ";
	}
}


void DrawGrid()
{
	system("CLS");	
		
	//!top col guide with the line
	for(int i=0; i<totalCol; i++)
	{	
		gotoxy(i*4+4, 3*totalRow+1+totalRow+2);
		textcolor(WHITE);
		cout<<"-----";
		textcolor(YELLOW);
		gotoxy(i*4+6, 2);
		cout<<i;
	}
	//! left row guide
	for(int i=0; i<totalRow; i++)
	{
		textcolor(LIGHTCYAN);
		gotoxy(2, i*4+5);
		cout<<i;
	}
	//! draw the left border and grid
	for(int i=0; i<totalRow; i++)
	{
		for(int j=0; j<totalCol; j++)
		{
			int xPos = 2*j+3+j+1;
			int yPos = 3*i+1+i+2;
			
			textcolor(WHITE);
			gotoxy(xPos, yPos);
			cout<<"-------------";
			
			if(LX == xPos && LY == yPos || tempJ+1 == j && LY == yPos)
			{
				textcolor(RED);
			}
			else
			{
				textcolor(WHITE);	
			}
			
			//! left border
			gotoxy(xPos+j, yPos+1);
			cout<<"|";
			gotoxy(xPos+j, yPos+2);
			cout<<"|";
			gotoxy(xPos+j, yPos+3);
			cout<<"|";
			
			textcolor(WHITE);
			
			textcolor(gridNode[i][j].color);
			
			for(int m=0; m<3; m++)
			{
				for(int n=0; n<3; n++)
				{
					gotoxy(xPos+n+j+1, yPos+m+1);
					cout<<gridNode[i][j].sprite[m][n];
				}
			}
		}
	}
	
	//! draw the right border
	for(int i=0; i<totalRow; i++)
	{
		int xPos = 2*totalCol+4+totalCol;
		int yPos = 3*i+1+i+2;
		if(tempJ == totalCol-1 && LY == yPos)
		{
			textcolor(RED);
		}
		else
		{
			textcolor(WHITE);
		}
		
		gotoxy(xPos+totalCol, yPos+1);
		cout<<"|";
		gotoxy(xPos+totalCol, yPos+2);
		cout<<"|";
		gotoxy(xPos+totalCol, yPos+3);
		cout<<"|";
		
		textcolor(WHITE);
	}
	
	if(mode == 2)
	{
		DisplayType();
	}
	else if(mode == 3)
	{
		DisplayType();
		gotoxy(42, 4);
		cout << "Remaining Rotation: ";
		gotoxy(42, 5);
		cout << 4 - gridNode[tempI][tempJ].RotateCounter;
	}
	
	gotoxy(42, 8);
	cout << "Steps Used: ";
	gotoxy(42, 9);
	cout << steps;

	gotoxy(10, totalRow+37);
	system("PAUSE");
}

void RotateGrid(int row, int col)
{
	if(gridNode[row][col].RotateCounter >= 4)
	{
		gridNode[row][col].type = BLOCK;
	}
	
	if(gridNode[row][col].type == STRAIGHT_HORIZONTAL)
	{
		gridNode[row][col].type = STRAIGHT_VERTICAL;
	}
	else if(gridNode[row][col].type == STRAIGHT_VERTICAL)
	{
		gridNode[row][col].type = STRAIGHT_HORIZONTAL;
	}
	else if(gridNode[row][col].type == LSHAPE_0_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_90_DEGREE;
	}
	else if(gridNode[row][col].type == LSHAPE_90_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_180_DEGREE;
	}
	else if(gridNode[row][col].type == LSHAPE_180_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_270_DEGREE;
	}
	else if(gridNode[row][col].type == LSHAPE_270_DEGREE)
	{
		gridNode[row][col].type = LSHAPE_0_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_0_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_90_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_90_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_180_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_180_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_270_DEGREE;
	}
	else if(gridNode[row][col].type == TSHAPE_270_DEGREE)
	{
		gridNode[row][col].type = TSHAPE_0_DEGREE;
	}
	
	//! changing the type after rotation, update the gridNode by invoke setType
	gridNode[row][col].SetType(gridNode[row][col].type);
}

void RotateGridMenu()
{
	int xPosRotate;
	int yPosRotate;
	if(GetAsyncKeyState(VK_SPACE) && gridNode[tempI][tempJ].type != BLOCK) //! to prevent the 4 connected-grid rotate in hard mode when one of them is block
	{
		xPosRotate = tempI;
		yPosRotate = tempJ;
		if(mode == 3) // extra features for hard mode
		{
			if(gridNode[xPosRotate][yPosRotate].type != EMPTY) //! To prevent rotate counter increase when inserting a grid type
			{
				gridNode[xPosRotate][yPosRotate].RotateCounter++;
			}
			//! For rotating all 4 grid together
			if(xPosRotate == 0 && yPosRotate == 2)
			{
				RotateGrid(0, 6);
				RotateGrid(5, 2);
				RotateGrid(5, 6);
			}
			else if(xPosRotate == 0 && yPosRotate == 6)
			{
				RotateGrid(0, 2);
				RotateGrid(5, 2);
				RotateGrid(5, 6);
			}
			else if(xPosRotate == 5 && yPosRotate == 2)
			{
				RotateGrid(0, 2);
				RotateGrid(0, 6);
				RotateGrid(5, 6);
			}
			else if(xPosRotate == 5 && yPosRotate == 6)
			{
				RotateGrid(0, 2);
				RotateGrid(0, 6);
				RotateGrid(5, 2);
			}
		}
		// for scoring
		if(gridNode[tempI][tempJ].type != DOT && gridNode[tempI][tempJ].type != EMPTY && gridNode[tempI][tempJ].type != TARGET && gridNode[tempI][tempJ].type != SOURCE)
		{
			steps++;
		}
		
		RotateGrid(xPosRotate, yPosRotate);
	}
	
	Unlink();
	ReinitializeLink();
	isSolve = ParseLink();
}

void InsertType(int row, int col)
{
	if(gridNode[row][col].type == EMPTY && tempType == 1)
	{
		gridNode[row][col].type = STRAIGHT_VERTICAL;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 2)
	{
		gridNode[row][col].type = STRAIGHT_HORIZONTAL;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 3)
	{
		gridNode[row][col].type = LSHAPE_90_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 4)
	{
		gridNode[row][col].type = LSHAPE_180_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 5)
	{
		gridNode[row][col].type = LSHAPE_270_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 6)
	{
		gridNode[row][col].type = LSHAPE_0_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 7)
	{
		gridNode[row][col].type = TSHAPE_90_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 8)
	{
		gridNode[row][col].type = TSHAPE_180_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 9)
	{
		gridNode[row][col].type = TSHAPE_270_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 10)
	{
		gridNode[row][col].type = TSHAPE_0_DEGREE;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 11)
	{
		gridNode[row][col].type = BLOCK;
	}
	else if(gridNode[row][col].type == EMPTY && tempType == 12)
	{
		gridNode[row][col].type = DOT;
	}

	//! changing the type after rotation, update the gridNode by invoke setType
	gridNode[row][col].SetType(gridNode[row][col].type);
}

void InsertMenu()
{
	int xPosInsert;
	int yPosInsert;	
	if(GetAsyncKeyState(VK_SPACE) && gridNode[tempI][tempJ].type == EMPTY) // only change the type given if space is pressed in empty grid
	{
		xPosInsert = tempI;
		yPosInsert = tempJ;
		InsertType(xPosInsert, yPosInsert);
		tempType = rand()%12 +1;
		// for scoring
		steps++;
	}
	
	Unlink();
	ReinitializeLink();
	isSolve = ParseLink();
}

int choice = -1;
void menu()
{
	gotoxy(14, 20);
	cout << "||";
	gotoxy(14, 21);
	cout << "||";
	gotoxy(14, 22);
	cout << "||";
	gotoxy(14, 23);
	cout << "||";
	gotoxy(14, 24);
	cout << "||";
	gotoxy(14, 25);
	cout << "||";
	
	gotoxy(46, 20);
	cout << "||";
	gotoxy(46, 21);
	cout << "||";
	gotoxy(46, 22);
	cout << "||";
	gotoxy(46, 23);
	cout << "||";
	gotoxy(46, 24);
	cout << "||";
	gotoxy(46, 25);
	cout << "||";
	
	gotoxy(20, 20);
	cout << "1. Start Game";
	gotoxy(20, 21);
	cout << "2. Select Difficulty";
	gotoxy(20, 22);
	cout << "3. High Scores";
	gotoxy(20, 23);
	cout << "4. Instructions";
	gotoxy(20, 24);
	cout << "5. Exit";
	gotoxy(20, 35);
	cout << "Your Choice: ";
	cin >> choice;
}

void ModeMenu()
{
	system("CLS");
	cout << "Current Mode: ";
	if(mode == 1)
	{
		cout << "Easy" << endl;
	}
	else if(mode == 2)
	{
		cout << "Medium" << endl;	
	}
	else if(mode == 3)
	{
		cout << "Hard" << endl;	
	}
	
	cout << "1. Easy" << endl;
	cout << "2. Medium" << endl;
	cout << "3. Hard" << endl;
	cin >> mode;
	
}

int main(int argc, char** argv)
{
	//! game windows console size
	system("mode con: cols=60 lines=44");
	srand(time(NULL));
	do
	{
		menu();
		steps = 0;
		if(choice == 1)
		{
			isEsc = false;
			isSolve = false;
			targetCounter = 0;
			InitializeGrid();
			Unlink();
			ReinitializeLink();
			isSolve = ParseLink();
			DrawGrid();
			do
			{
				if(mode == 1)
				{
					RotateGridMenu();
					Move();
					DrawGrid();	
				}
				else if(mode == 2)
				{
					InsertMenu();
					Move();
					DrawGrid();	
				}
				else if(mode == 3)
				{
					RotateGridMenu();
					InsertMenu();
					Move();
					DrawGrid();	
				}
				
				if(GetAsyncKeyState(VK_ESCAPE)) // Exit to main menu without complete
				{
					isEsc = true;
					isSolve = true;	
				}		
			}while(!isSolve);
			system("CLS");
			
			if(isEsc == false)
			{
				gotoxy(20, 10);
				string pName;
				cout << "Enter your name: ";
				gotoxy(20, 11);
				cin >> pName;
				int score = steps;
				setHighscore(mode, pName, score);
				system("CLS");
				HighScoreMenu();	
			}
		}
		else if(choice == 2)
		{
			ModeMenu();
			system("CLS");
			choice = -1;
		}
		else if(choice == 3)
		{
			HighScoreMenu();
		}
		else if(choice == 4)
		{
			system("CLS");
			gotoxy(10, 10);
			cout << "1. Connect all the target to win the game";
			gotoxy(10, 12);
			cout << "2. Use arrow key to move and space to action";
			gotoxy(10, 14);
			cout << "3. Press Esc to back to main menu";
			gotoxy(10, 32);
			system("PAUSE");
			system("CLS");
		}
		else if(choice == 5)
		{
			isExit = true;
		}
		
	}while(!isExit);
	
	system("PAUSE");
	return 0;
}

