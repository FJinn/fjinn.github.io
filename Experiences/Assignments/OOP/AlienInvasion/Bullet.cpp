#include "AllHeaderFiles.h"

Bullet::Bullet(BULLET_TYPE type)
{
	isReverseDirection = false;
	
	if(type == STRAIGHT)
	{
		row = 1;
		column = 1;
		direction = NORTH;
		char tempCharArray [1][1] =
		{
			{'^'}
		};
		
		CharArray = new char*[row];
		for(int i=0; i<row; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		
		color = LIGHTCYAN;
		x = 20;
		y = 15;
	}
	else if(type == DUO)
	{
		row = 1;
		column = 3;
		direction = NORTH;
		char tempCharArray [1][3] =
		{
			{'^', ' ', '^'}
		};
		
		CharArray = new char*[row];
		for(int i=0; i<row; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		
		color = LIGHTCYAN;
		x = 20;
		y = 15;
	}
	else if(type == TRIPLE)
	{
		row = 1;
		column = 3;
		direction = NORTH;
		char tempCharArray [1][3] =
		{
			{'^', '^', '^'}
		};
		
		CharArray = new char*[row];
		for(int i=0; i<row; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		
		color = LIGHTCYAN;
		x = 20;
		y = 15;
	}
	else if(type == LASER)
	{
		row = 3;
		column = 1;
		direction = NORTH;
		char tempCharArray [3][1] =
		{
			{'^'},
			{'^'},
			{'^'}
		};
		
		CharArray = new char*[row];
		for(int i=0; i<row; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		
		color = LIGHTCYAN;
		x = 20;
		y = 15;
	}
	else if(type == ZIGZAG)
	{
		row = 5;
		column = 3;
		direction = NORTH;
		char tempCharArray [5][3] =
		{
			{' ', ' ', '^'},
			{' ', '^', ' '},
			{'^', ' ', ' '},
			{' ', '^', ' '},
			{' ', ' ', '^'},
		};
		
		CharArray = new char*[row];
		for(int i=0; i<row; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		
		color = LIGHTCYAN;
		x = 20;
		y = 15;
	}
	else if(type == BOMB)
	{
		row = 1;
		column = 1;
		direction = NORTH;
		char tempCharArray [1][1] =
		{
			{'o'}
		};
		
		CharArray = new char*[row];
		for(int i=0; i<row; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		
		color = LIGHTCYAN;
		x = 20;
		y = 15;
	}
	else if(type == STAR)
	{
		row = 5;
		column = 5;
		direction = NORTH;
		char tempCharArray [5][5] =
		{
			{' ',' ','^',' ',' '},
			{' ','^',' ','^',' '},
			{'<',' ',' ',' ','>'},
			{' ',' ','^',' ',' '},
			{' ','v',' ','v',' '}
		};
		
		CharArray = new char*[row];
		for(int i=0; i<row; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		
		color = YELLOW;
		x = 20;
		y = 15;
	}
	
	
	isAlive = true;
}

void Bullet::Update()
{
	if(CheckTopBoundary() == false && CheckBottomBoundary() == false)
	{
		if(!isReverseDirection)
		{
			if(direction == NORTH)
			{
				MoveUp();
			}
			else if(direction == EAST)
			{
				MoveRight();
			}
			else if(direction == WEST)
			{
				MoveLeft();
			}
			else if(direction == SOUTH)
			{
				MoveDown();
			}
			else if(direction == NORTH_EAST)
			{
				MoveUp();
				MoveRight();
			}
			else if(direction == NORTH_WEST)
			{
				MoveUp();
				MoveLeft();
			}
			else if(direction == SOUTH_EAST)
			{
				MoveDown();
				MoveRight();
			}
			else if(direction == SOUTH_WEST)
			{
				MoveDown();
				MoveLeft();
			}
		}
		else
		{
			if(direction == NORTH)
			{
				MoveDown();
			}
			else if(direction == EAST)
			{
				MoveLeft();
			}
			else if(direction == WEST)
			{
				MoveRight();
			}
			else if(direction == SOUTH)
			{
				MoveUp();
			}
			else if(direction == NORTH_EAST)
			{
				MoveDown();
				MoveLeft();
			}
			else if(direction == NORTH_WEST)
			{
				MoveDown();
				MoveRight();
			}
			else if(direction == SOUTH_EAST)
			{
				MoveUp();
				MoveLeft();
			}
			else if(direction == SOUTH_WEST)
			{
				MoveUp();
				MoveRight();
			}
		}
	}
	else if(CheckTopBoundary() || CheckBottomBoundary() || CheckLeftBoundary() || CheckRightBoundary())
	{
		isAlive = false;
	}
	
}
