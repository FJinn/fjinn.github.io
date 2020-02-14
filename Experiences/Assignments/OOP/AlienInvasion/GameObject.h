#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "AllHeaderFiles.h"

using namespace std;

class GameObject
{
	public:
		//! x,y == location in the game world
		//! x0,y0 == store previous x, y location
		//! row,column == for the sprite array size(3,3) (3,5)
		//! speedX, speedY == movement speed x++, x--, y++, y--
		//! colour-> colour for the sprites 
		int x, y, x0, y0, row, column, speedX, speedY, color;
		char** CharArray; //! sprite
		
		GameObject();
		
		void DrawTrail();
		void Draw();
		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
		bool CheckLeftBoundary();
		bool CheckRightBoundary();
		bool CheckTopBoundary();
		bool CheckBottomBoundary();
		virtual void Update() = 0;
};

#endif
