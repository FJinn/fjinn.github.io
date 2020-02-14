#include "AllHeaderFiles.h"

GameObject::GameObject()
{
	speedX =1;
	speedY=1;
	y0 =-1;
	x0 = -1;
}

void GameObject::DrawTrail()
{
	for(int i=0; i<row; i++)
	{
		for(int j=0; j<column; j++)
		{
			gotoxy(x0+j, y0+i);
			if(y0+i > BOUNDARY_TOP &&
			   y0+i < BOUNDARY_BOTTOM &&
			   x0+j > BOUNDARY_LEFT &&
			   x0+j < BOUNDARY_RIGHT )
			{
				cout<<" ";
			}
		}
	}
}

void GameObject::Draw()
{
	//! erase old
	if(x0 != -1 && y0 != -1 && y0 != BOUNDARY_TOP && (x0 != x || y0 != y))
	{
		DrawTrail();
	}
	textcolor(color);
	
	for(int i=0; i<row; i++)
	{
		gotoxy(x, y+i);
		for(int j=0; j<column; j++)
		{
			if(y+i > BOUNDARY_TOP && 
			   y+i < BOUNDARY_BOTTOM &&
			   x+j > BOUNDARY_LEFT &&
			   x+j < BOUNDARY_RIGHT)
			   {
			   	cout<<CharArray[i][j];
			   }
			   else
			   {
			   		gotoxy(x+j, y+i);
			   }
		}
	}
	textcolor(WHITE);
	x0=x; //! update the old position
	y0=y;
}

void GameObject::MoveLeft()
{
	x -= speedX;
}

void GameObject::MoveRight()
{
	x += speedX;
}

void GameObject::MoveUp()
{
	y -= speedY;
}

void GameObject::MoveDown()
{
	y += speedY;
}

bool GameObject::CheckLeftBoundary()
{//!   3      5           +  1 = 6  
/*	if(x <= BOUNDARY_LEFT + speedX)
	{//         1          1
		int tempSpeedX = speedX;
		//       3- 5  -1 = -3
		speedX = x-BOUNDARY_LEFT -1;
		MoveLeft();
		//!  1     1
		speedX = tempSpeedX;
		return true;
	}*/
	
	if(x<=BOUNDARY_LEFT + speedX)
	{
		return true;
	}
	return false;
}

bool GameObject::CheckRightBoundary()
{
/*	if(x>= BOUNDARY_RIGHT - speedX - column)
	{
		int tempSpeedX = speedX;
		speedX = BOUNDARY_RIGHT - x - column -1;
		MoveRight();
		speedX = tempSpeedX;
		return true;
	}*/
	if(x>=BOUNDARY_RIGHT - speedX - column)
	{
		return true;
	}
	return false;
}

bool GameObject::CheckTopBoundary()
{
/*	if(y<=BOUNDARY_TOP + speedY)
	{
		int tempSpeedY = speedY;
		speedY = y-BOUNDARY_TOP -1;
		MoveUp();
		speedY = tempSpeedY;
		return true;
	}*/
	if(y<=BOUNDARY_TOP + speedY)
	{
		return true;
	}
	return false;
}

bool GameObject::CheckBottomBoundary()
{
/*	if(y>=BOUNDARY_BOTTOM -speedY - row)
	{
		int tempSpeedY = speedY;
		speedY = BOUNDARY_BOTTOM - y - row -1;
		MoveDown();
		speedY= tempSpeedY;
		return true;
	}*/
	if(y>=BOUNDARY_BOTTOM -speedY - row)
	{
		return true;
	}
	return false;
}

