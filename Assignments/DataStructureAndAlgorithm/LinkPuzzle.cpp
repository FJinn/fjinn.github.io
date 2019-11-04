#include <iostream>
#include <ctime>
#include "windows.h"
#include <cmath>
#include <limits>
#include <vector>
#include "conio_yp.h"
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
	STRAIGHT,
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
	TOTAL_TYPE
};

struct Node
{
	GRID_TYPE type;
	char **sprite;
	int color;
	int colorOriginal;
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
		color = BLACK;
		
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

void MarkLink(Node* node, DIRECTION direction)
{
	node->color = YELLOW;
	//! north node
	if(node->northNode != NULL && direction != NORTH)
	{
		MarkLink(node->northNode, SOUTH);
	}
	//! southNode pointer
	if(node->southNode != NULL && direction != SOUTH)
	{
		MarkLink(node->southNode, NORTH);
	}
	//! eastNode pointer
	if(node->eastNode != NULL && direction != EAST)
	{
		MarkLink(node->eastNode, WEST);
	}
	//! westNode pointer
	if(node->westNode != NULL && direction != WEST)
	{
		MarkLink(node->westNode, EAST);
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
	
	if(targetCounter >= 3)
	{
		isAllConnected = true;
	}	
	else 
	{
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
	GRID_TYPE tempGrid[totalRow][totalCol]=
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
	ParseLink();
}
void DrawGrid()
{
system("CLS");
	//!top col guide with the line
	for(int i=0; i<totalCol; i++)
	{
		textcolor(WHITE);
		gotoxy(i*4+4, 3*totalRow+1+totalRow+2);
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
			textcolor(WHITE);
			int xPos = 2*j+3+j+1;
			int yPos = 3*i+1+i+2;
			gotoxy(xPos, yPos);
			cout<<"-------------";
			//! left border
			gotoxy(xPos+j, yPos+1);
			cout<<"|";
			gotoxy(xPos+j, yPos+2);
			cout<<"|";
			gotoxy(xPos+j, yPos+3);
			cout<<"|";
			
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
		textcolor(WHITE);
		int xPos = 2*totalCol+4+totalCol;
		int yPos = 3*i+1+i+2;
		gotoxy(xPos+totalCol, yPos+1);
		cout<<"|";
		gotoxy(xPos+totalCol, yPos+2);
		cout<<"|";
		gotoxy(xPos+totalCol, yPos+3);
		cout<<"|";
	}
}

void RotateGrid(int row, int col)
{
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

void Move()
{
	
	if(GetAsyncKeyState(VK_LEFT))
	{
		
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		
	}
}

void RotateGridMenu()
{
	int xPosRotate;
	int yPosRotate;
	textcolor(YELLOW);
	gotoxy(2,28);
	cout<<"Key in COL value for rotation: ";
	while(!(cin>>yPosRotate) || yPosRotate<0 || yPosRotate>8)
	{
		cin.clear();
		gotoxy(2, 28);
		cout<<"                           ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	textcolor(CYAN);
	gotoxy(2,30);
	cout<<"Key in ROW value for rotation: ";
	while(!(cin>>xPosRotate) || xPosRotate<0 || xPosRotate>8)
	{
		cin.clear();
		gotoxy(2, 28);
		cout<<"                           ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	textcolor(WHITE);
	
	RotateGrid(xPosRotate, yPosRotate);
	Unlink();
	ReinitializeLink();
	isSolve = ParseLink();
	gotoxy(2,32);
	system("PAUSE");
}

int choice = -1;
void menu()
{
	cout << "1. Start Game" << endl;
	cout << "2. Select Difficulty" << endl;
	cout << "3. High Scores" << endl;
	cout << "4. Exit" << endl;
	cin >> choice;
}

int main(int argc, char** argv)
{
	//! game windows console size
	system("mode con: cols=60 lines=33");
	menu();
	if(choice == 1)
	{
		InitializeGrid();
		Unlink();
		ReinitializeLink();
		isSolve = ParseLink();
		DrawGrid();
		do
		{
			RotateGridMenu();
			DrawGrid();	
		}while(!isSolve);
	}
	
	system("PAUSE");
	return 0;
}

