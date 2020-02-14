#include "AllHeaderFiles.h"

Enemy::Enemy(ENEMY_TYPE enemyType)
{
	if(enemyType == NORMAL)
	{
		row = 3;
		column = 3;
		killScore = 10;
		
		char tempCharArray[3][3] =
		{
			{'x','x','x'},
			{'1','x','1'},
			{' ','x',' '}
		};
		CharArray = new char*[row];
		for(int i=0; i<3; i++)
		{
			CharArray[i] = new char[column];
			for(int j=0; j<column; j++)
			{
				CharArray[i][j] = tempCharArray[i][j];
			}
		}
		color = LIGHTRED;
		x=20;
		y=10;
		updateDelayDuration = 2;
		
		AddMove(SOUTH, 100);
	}
	else if(enemyType == BOSS)
	{
		row = 5;
		column = 5;
		killScore = 50;
		
		char tempCharArray[5][5] =
		{
			{'x','x','x','x','x'},
			{'x','x','1','x','x'},
			{' ','x','1','x',' '},
			{'x','x','1','x','x'},
			{' ',' ','x',' ',' '}
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
		color = LIGHTRED;
		x=20;
		y=10;
		updateDelayDuration = 2;
		
		AddMove(SOUTH, 100);
	}
	else if(enemyType == ENEMY01)
	{
		row = 5;
		column = 5;
		killScore = 20;
		
		char tempCharArray[4][4] =
		{
			{'x','x','x','x'},
			{' ','x','x',' '},
			{' ','x','x',' '},
			{' ','x','x',' '}
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
		color = LIGHTRED;
		x=20;
		y=10;
		updateDelayDuration = 2;
		
		AddMove(SOUTH_EAST, 100);
	}
	else if(enemyType == ENEMY02)
	{
		row = 5;
		column = 5;
		killScore = 25;
		
		char tempCharArray[5][5] =
		{
			{'x','x','x','x','x'},
			{'x','x','1','x','x'},
			{' ','x','1','x',' '},
			{' ','x','1','x',' '},
			{' ',' ','x',' ',' '}
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
		color = LIGHTRED;
		x=20;
		y=10;
		updateDelayDuration = 2;
		
		AddMove(SOUTH_WEST, 100);
	}
	else if(enemyType == ENEMY03)
	{
		row = 5;
		column = 5;
		killScore = -30;
		
		char tempCharArray[5][5] =
		{
			{'x','x','x','x','x'},
			{'x',' ','1',' ','x'},
			{' ',' ','1',' ',' '},
			{' ',' ','1',' ',' '},
			{' ',' ','1',' ',' '}
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
		color = LIGHTRED;
		x=20;
		y=10;
		updateDelayDuration = 2;
		
		AddMove(EAST, 100);
	}
	else if(enemyType == ENEMY04)
	{
		row = 5;
		column = 5;
		killScore = -30;
		
		char tempCharArray[5][5] =
		{
			{'x','x','x'},
			{'x','x','x'},
			{'x','x','x'}
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
		color = LIGHTRED;
		x=20;
		y=10;
		updateDelayDuration = 2;
		
		AddMove(EAST, 100);
	}
	second = false;
	updateDelayTimer = 0;
	this->enemyType = enemyType;
	isAlive = true;
	moveTimer = 0;
	
	shootDelayTimer = 0;
	shootDelayDuration = 3;
	enableShooting = false;
	bulletType = STRAIGHT;
}

void Enemy::AddMove(DIRECTION direction, int time)
{
	MoveInfo tempMoveInfo;
	tempMoveInfo.direction = direction;
	tempMoveInfo.time = time;
	tempMoveInfo.isCompleted = false;
	moveList.push_back(tempMoveInfo);
}

void Enemy::UpdateMove()
{
	for(int i=0; i< moveList.size(); i++)
	{
		if(moveList[i].isCompleted == true)
		{
			second = true;
			continue;
		}
		if(moveTimer<=moveList[i].time)
		{
			if(moveList[i].direction == NORTH)
			{
				MoveUp();
			}
			else if(moveList[i].direction == EAST)
			{
				MoveRight();
			}
			else if(moveList[i].direction == WEST)
			{
				MoveLeft();
			}
			else if(moveList[i].direction == SOUTH)
			{
				MoveDown();
			}
			else if(moveList[i].direction == NORTH_EAST)
			{
				MoveUp();
				MoveRight();
			}
			else if(moveList[i].direction == NORTH_WEST)
			{
				MoveUp();
				MoveLeft();
			}
			else if(moveList[i].direction == SOUTH_EAST)
			{
				MoveDown();
				MoveRight();
			}
			else if(moveList[i].direction == SOUTH_WEST)
			{
				MoveDown();
				MoveLeft();
			}
		}
		else
		{
			moveList[i].isCompleted = true;
		}
	}
}

void Enemy::Update()
{
	updateDelayTimer++;
	moveTimer++;
	
	shootDelayTimer++;
	
	if(updateDelayTimer<updateDelayDuration)
	{
		return;
	}
	updateDelayTimer = 0;
	
	if(shootDelayTimer<shootDelayDuration && isAlive)
	{
		shootDelayTimer = 0;
		shoot();
	}
	
	if(CheckBottomBoundary() == false)
	{
//		MoveDown();
		UpdateMove();
	}
	else
	{
		isAlive = false;
	}
	
	if(CheckLeftBoundary() || CheckRightBoundary())
	{
		isAlive = false;
	}
	
	if(!isAlive)
	{
		DrawTrail();
		x = BOUNDARY_LEFT -10;
		y = BOUNDARY_BOTTOM +40;
		x0 = x;
		y0 = y;
		enableShooting = false;
	}
	
	for(int i=0; i<bulletList.size(); i++)
	{
		bulletList[i].Update();
		if(bulletList[i].isAlive == false)
		{
			bulletList[i].DrawTrail();
			
			vector<Bullet> temp;
			for(int j=bulletList.size()-1; j>-1; j--)
			{
				if(j != i)
				{	
					temp.push_back(bulletList.back());
				}
				bulletList.pop_back();
			}
			bulletList = temp;
			i = 0;
			
		}
		else
		{
			bulletList[i].Draw();
		}

	}
}

void Enemy::shoot()
{
	if(bulletList.size() < MAX_BULLET)
	{
		//bullet creation
		Bullet newBullet(bulletType);
		newBullet.isReverseDirection = true;
		newBullet.direction = NORTH;
		// bullet spawning location
		newBullet.x = x+1;
		newBullet.y = y + column;
		newBullet.speedY += 6;
		// store to the bullet vector list
		bulletList.push_back(newBullet);
	}
}
