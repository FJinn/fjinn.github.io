#include "AllHeaderFiles.h"

Player::Player()
{
	row = 3;
	column = 3;
	
	life = 3;
	
	char tempCharArray[3][3] =
	{
		{' ','1',' '},
		{'1','1','1'},
		{'#','#','#'}
	};
	
	CharArray = new char*[row];
	for(int i=0; i<row; i++)
	{
		CharArray[i] = new char [column];
		for(int j=0; j<column; j++)
		{
			CharArray[i][j] = tempCharArray[i][j];
		}
	}
	color = YELLOW;
	x =20;
	y =20;
	health = 100;
	score = 0;
	
	shootDelayTimer = 0;
	shootDelayDuration = 10;
}

void Player::Update()
{
	shootDelayTimer++;
	
	if(GetAsyncKeyState('A'))
	{
		if(CheckLeftBoundary() == false)
		{
			MoveLeft();
		}
	}
	if(GetAsyncKeyState('D'))
	{
		if(CheckRightBoundary() == false)
		{
			MoveRight();
		}
	}
	if(GetAsyncKeyState('W'))
	{
		if(CheckTopBoundary() == false)
		{
			MoveUp();
		}
	}
	if(GetAsyncKeyState('S'))
	{
		if(CheckBottomBoundary() == false)
		{
			MoveDown();
		}
	}
	
	if(GetAsyncKeyState(VK_SPACE))
	{
		if(shootDelayTimer > shootDelayDuration)
		{
			Shoot(type);
			shootDelayTimer = 0;
		}
	}
	
	for(int i=0; i<bulletList.size(); i++)
	{
		bulletList[i].Update();
		if(bulletList[i].isAlive == false)
		{
			bulletList[i].DrawTrail();
	//		bulletList.erase(bulletList.begin()+i);
			
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
	
	if(score%1000 == 0)
	{
		if(life <3)
		{
			life++;
		}
	}
	
	if(life> 3)
	{
		life = 3;
	}
	if(health <= 0)
	{
		life--;
		health = 100;
	}
	
}

void Player::Shoot(BULLET_TYPE type)
{
	if(bulletList.size() < MAX_BULLET)
	{
		//bullet creation
		Bullet newBullet(type);
		// bullet spawning location
		newBullet.x = x+1;
		newBullet.y = y;
		// store to the bullet vector list
		bulletList.push_back(newBullet);
	}
}
