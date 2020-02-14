#include "AllHeaderFiles.h"

Item::Item(ITEM_TYPE type)
{
	if(type == HEALTH_PACK)
	{
		row = 1;
		column = 1;
		char tempCharArray [1][1] =
		{
			{'H'}
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
	else if(type == DUO_PACK)
	{
		row = 1;
		column = 1;
		char tempCharArray [1][1] =
		{
			{'D'}
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
		
		bulletType = DUO;
	}
	else if(type == TRIPLE_PACK)
	{
		row = 1;
		column = 1;
		char tempCharArray [1][1] =
		{
			{'T'}
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
		
		bulletType = TRIPLE;
		shootDelayDuration = 2;
	}
	else if(type == LASER_PACK)
	{
		row = 1;
		column = 1;
		char tempCharArray [1][1] =
		{
			{'L'}
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
		
		bulletType = LASER;
		shootDelayDuration = 8;
	}
	else if(type == ZIGZAG_PACK)
	{
		row = 1;
		column = 1;
		char tempCharArray [1][1] =
		{
			{'Z'}
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
		
		bulletType = ZIGZAG;
		shootDelayDuration = 10;
	}
	else if(type == STAR_PACK)
	{
		row = 1;
		column = 1;
		char tempCharArray [1][1] =
		{
			{'S'}
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
		
		bulletType = STAR;
		shootDelayDuration = 15;
	}
	else if(type == BOMB_PACK)
	{
		row = 1;
		column = 1;
		char tempCharArray [1][1] =
		{
			{'B'}
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
		
		bulletType = BOMB;
	}
	
	itemType = type;
	isAlive = true;
}

void Item::Update()
{
	if(CheckBottomBoundary() == false)
	{
		MoveDown();
	}
	else
	{
		isAlive = false;
	}
}
