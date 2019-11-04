/*************************************************************************************************************************************************************

Assignment 2 – Inheritance
==========================

• Create a simple battle simulator game using console application (30%)
//! - Implement a battle simulator gameplay (10%)
//! - Implement at least 10 different classes (10%)
//! - Implement at least 1 base class with multiple derived classes (4%)
//! - Implement either a static variable, static function or inline function in a class (2%)
//! - Implement a virtual function in a class (2%)
//! - Implement a pure virtual function and an abstract class (2%)

Deadline : 29th March 2017. Email your source codes WITHOUT exe to anonymoushomosapiens@gmail.com

*************************************************************************************************************************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "conio_yp.h"
#include <windows.h> //! 1. use to set console title
					 //! 2. for 'sleep (milliseconds)'\
					 
#include <iomanip>   //! For 'setw(n)', setting the field width to be used on output operations
#include <cmath>
					 
//! ASCII Table
# define indicator 219
# define jungle 176
# define space 255
# define grass 251
# define water 247
# define leftside 222
# define rightside 221
# define topside 223
# define bottomside 220
# define whole 219
# define entrance 255
# define hero 234
# define professor 153
# define pball 233

using namespace std;

enum GAME_STATE
{
	MAIN_MENU = 0,
	CHARACTER_SELECTION,
	SHOW_GUI,
	MONSTER_SELECTION,
	BATTLE
};

enum PLAYER_GENDER
{
	BOY = 0,
	GIRL
};

enum PLAYER_POSITION
{
	INDOOR = 0,
	OUTDOOR
};

enum STARTER_MONSTER
{
	EAGGLE = 0,
	SQUILLA,
	HORNET
};

enum ENEMY_MONSTER
{
	LYNX = 0,
	FRUGG,
	TOTAL_ENEMY
};

GAME_STATE gameState = MAIN_MENU;

bool captured[TOTAL_ENEMY] = {false, false};
const int screenWidth = 80;
const int screenHeight = 30;
int choice = -1;

class Map
{
	public:
		static const int row = 21;
		static const int col = 49;
		static const int offsetX = 4;
		static const int offsetY = 3;
		char map[row][col];
		
		virtual void initializeMap() = 0;
		
		virtual void colorMap(int x, int y)
		{
			if (map[y][x] == (char)jungle)
				textcolor(GREEN);
			
			else if (map[y][x] == (char)grass)
				textcolor(LIGHTGREEN);
			
			else if (map[y][x] == (char)water)
				textcolor(LIGHTBLUE);
			
			else if (map[y][x] == (char)leftside || map[y][x] == (char)rightside 
					|| map[y][x] == (char)bottomside || map[y][x] == (char)topside 
					|| map[y][x] == (char)whole)
				textcolor(WHITE);
				
			else if (map[y][x] == (char)professor)
				textcolor(WHITE);
		}
		
		virtual void displayMap()
		{
			for(int y=0; y<row; y++)
			{
				for(int x=0; x<col; x++)
				{
					gotoxy(x+offsetX, y+offsetY);
					colorMap(x, y);
					cout<<map[y][x];
				}
			}
		}
};

class Outdoor : public Map
{
	public:
		void initializeMap()
		{
			//! 0 == Space
			//! 1 == Jungle
			//! 2 == Grass
			//! 3 == Water
			char designMap[row][col] =
			{
			//   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 
				{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
				{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
				{1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,3,0,'b','w','w','w','b',0,0,0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 0, 0,2,2,'l','w','t','w','r',0,0,0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 2, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 2, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1},
				{1, 1, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1}, //10
				{1, 1, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,'b','w','w','w','b',0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,'b','w','w','w','b',0,0,0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0,0,0,'l','w','t','w','r',0,0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,'l','w','t','w','r',0,0,0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
				{1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1},
				{1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1},
				{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, //20
				{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} 
			};
			for(int y=0; y<row; y++)
			{
				for(int x=0; x<col; x++)
				{
					map[y][x] = designMap[y][x];
					
					if (map[y][x] == (char)0)
						map[y][x]= (char)space;
					
					else if (map[y][x] == (char)1)
						map[y][x]= (char)jungle;
					
					else if (map[y][x] == (char)2)
						map[y][x]= (char)grass;
					
					else if (map[y][x] == (char)3)
						map[y][x]= (char)water;
					
					else if (map[y][x] == 'l')
						map[y][x]= (char)leftside;
					
					else if (map[y][x] == 'r')
						map[y][x]= (char)rightside;
					
					else if (map[y][x] == 'b')
						map[y][x]= (char)bottomside;
					
					else if (map[y][x] == 't')
						map[y][x]= (char)topside;
					
					else if (map[y][x] == 'w')
						map[y][x]= (char)whole;
					
					//else if (map[y][x] == 'e')
					//	map[y][x]= (char)entrance;
				}
			}
		}
		
		void displayMap()
		{
			for(int y=0; y<row; y++)
			{
				for(int x=0; x<col; x++)
				{
					gotoxy(x+offsetX, y+offsetY);
					colorMap(x, y);
					cout<<map[y][x];
				}
			}
			
			textcolor(DARKGRAY);
			gotoxy(16+offsetX, 20+offsetY);
			cout<<"Pocket Monster V2";
		}
};

Outdoor* outdoor;

class Room01 : public Map
{
	public:
		void initialize()
		{
			//! 0 == Space
			//! 1 == Proffesor
			//! 2 == Water
			char designRoom[row][col] = 
			{
			//   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b','b',  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //10
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,'w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,'w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,'w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,'w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,'w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','w','w','w','w','w','w','w','w','w','w','w','r','e','l','w','w','w','w','w','w','w','w','w','w','w','w','w', 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //20
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
			};
			for (int y = 0; y < row; y++)
			{
				for (int x = 0; x < col; x++)
				{
					map[y][x] = designRoom[y][x];
					
					if (map[y][x] == (char)0)
						map[y][x] = (char)space;
				
					else if (map[y][x] == (char)1)
						map[y][x] = (char)professor;
						
					else if (map[y][x] == (char)2)
						map[y][x] = (char)water;
						
					else if (map[y][x] == 'l')
						map[y][x] = (char)leftside;
					
					else if (map[y][x] == 'r')
						map[y][x] = (char)rightside;
					
					else if (map[y][x] == 'b')
						map[y][x] = (char)bottomside;
					
					else if (map[y][x] == 't')
						map[y][x] = (char)topside;
					
					else if (map[y][x] == 'w')
						map[y][x] = (char)whole;
				}
			}
		}
};

class Room02 : public Map
{
	public:
		void initialize()
		{
			//! 0 == Space
			//! 1 == Proffesor
			//! 2 == Water
			char designRoom[row][col] = 
			{
			//   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'t',  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,'w','w','w','w','w','w','r',  0,'l','w','w','w','w','w','w','w','w','w','w',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,'w','t',  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','r',  0,  0,'w','r',  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //10
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','r',  0,  0,'w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,'w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,'w',  0,  0,  0,'b',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,'t',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'l','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','w','w','w','w','w','w','w','w','w','w','w','r','e','l','w','w','w','w','w','w','w','w','w','w','w','w','w', 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //20
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
			};
			for (int y = 0; y < row; y++)
			{
				for (int x = 0; x < col; x++)
				{
					map[y][x] = designRoom[y][x];
					
					if (map[y][x] == (char)0)
						map[y][x] = (char)space;
						
					else if (map[y][x] == (char)2)
						map[y][x] = (char)water;
						
					else if (map[y][x] == 'l')
						map[y][x] = (char)leftside;
					
					else if (map[y][x] == 'r')
						map[y][x] = (char)rightside;
					
					else if (map[y][x] == 'b')
						map[y][x] = (char)bottomside;
					
					else if (map[y][x] == 't')
						map[y][x] = (char)topside;
					
					else if (map[y][x] == 'w')
						map[y][x] = (char)whole;
				}
			}
		}
};

class Room03 : public Map
{
	public:
		void initialize()
		{
			//! 0 == Space
			//! 1 == Proffesor
			//! 2 == Water
			char designRoom[row][col] = 
			{
			//   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','w','w','w','w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w','w','w','w','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,'b','b','b','b','b','b','b','b','b','b','b','b','b','b','b',  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'l','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'l','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,'b','b','b','b','b','b','b','b','b',  0,  0,  0,  0,  0,  0,  0,'l','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,'t','t','t','t','t','t','t','t','t',  0,  0,  0,  0,  0,  0,  0,'l','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,'b','b',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'b','b',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,'t','t',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'t','t',  0,  0,  0,'w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'l','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'l','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w',  0,  0,'b','b','b','b','b',  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'b','b','b','b','w','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'w','w','w','w','w','w','w','w','w','w','w','w','w','r','e','l','w','w','w','w','w','w','w','w','w','w','w','w','w', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}	
			};
			for (int y = 0; y < row; y++)
			{
				for (int x = 0; x < col; x++)
				{
					map[y][x] = designRoom[y][x];
					
					if (map[y][x] == (char)0)
						map[y][x] = (char)space;
						
					else if (map[y][x] == (char)2)
						map[y][x] = (char)water;
						
					else if (map[y][x] == 'l')
						map[y][x] = (char)leftside;
					
					else if (map[y][x] == 'r')
						map[y][x] = (char)rightside;
					
					else if (map[y][x] == 'b')
						map[y][x] = (char)bottomside;
					
					else if (map[y][x] == 't')
						map[y][x] = (char)topside;
					
					else if (map[y][x] == 'w')
						map[y][x] = (char)whole;
				}
			}
		}
};

class Indicator
{	
	public:
		bool isExit;
		char key;
		int choice;
		int tolChoice;
		int x, y;
		int prevX, prevY;
		int spacingX, spacingY;
		int cursorX;
		int cursorY;
		
		virtual void moveIndicator() = 0;
};

class MainMenuIndicator : public Indicator
{
	public:
		void moveIndicator()
		{
			isExit = false;
			choice = 1;
			tolChoice = 2;
			x = 35;
			y = 21;
			spacingX = 0;
			spacingY = 2;
			cursorX = wherex();
			cursorY = wherey();
			
			do
			{
				prevX = x;
				prevY = y;
				
				textcolor(LIGHTCYAN);
				gotoxy(x, y);
				cout << (char)indicator;
				gotoxy(cursorX, cursorY);
				
				key = getch();
				//! Take key state
				//! Virtual-key codes
				if ((key == 'w' || key == 'W') && (choice-1) > 0)
				{
					choice -= 1;
					y -= spacingY;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				else if ((key == 's' || key == 'S') && (choice+1) <= tolChoice)
				{
					choice += 1;
					y += spacingY;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				//! Get ENTER to end loop
				else if (key == (VK_RETURN) )
					isExit = true;
					
			}while(!isExit);
		}
};

class CharSelIndicator : public Indicator
{
	public:
		void moveIndicator()
		{
			isExit = false;
			choice = 1;
			tolChoice = 2;
			x = 19;
			y = 23;
			spacingX = 36;
			spacingY = 0;
			cursorX = wherex();
			cursorY = wherey();
			
			do
			{
				prevX = x;
				prevY = y;
				
				textcolor(LIGHTCYAN);
				gotoxy(x, y);
				cout << (char)indicator;
				gotoxy(cursorX, cursorY);
				
				key = getch();
				//! Take key state
				//! Virtual-key codes
				if ((key == 'a' || key == 'A') && (choice-1) > 0)
				{
					choice -= 1;
					x -= spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				else if ((key == 'd' || key == 'D') && (choice+1) <= tolChoice)
				{
					choice += 1;
					x += spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				//! Get ENTER to end loop
				else if (key == (VK_RETURN) )
					isExit = true;
					
			}while(!isExit);
		}
};

class MonsSelIndicator : public Indicator
{
	public:
		void moveIndicator()
		{
			isExit = false;
			choice = 1;
			tolChoice = 3;
			x = 14;
			y = 19;
			spacingX = 23;
			spacingY = 0;
			cursorX = wherex();
			cursorY = wherey();
			
			do
			{
				prevX = x;
				prevY = y;
				
				textcolor(LIGHTCYAN);
				gotoxy(x, y);
				cout << (char)indicator;
				gotoxy(cursorX, cursorY);
				
				key = getch();
				//! Take key state
				//! Virtual-key codes
				if ((key == 'a' || key == 'A') && (choice-1) > 0)
				{
					choice -= 1;
					x -= spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				else if ((key == 'd' || key == 'D') && (choice+1) <= tolChoice)
				{
					choice += 1;
					x += spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				//! Get ENTER to end loop
				else if (key == (VK_RETURN) )
					isExit = true;
					
			}while(!isExit);
		}
};

class BattleChoice01 : public Indicator
{
	public:
		void moveIndicator()
		{
			isExit = false;
			choice = 1;
			tolChoice = 3;
			x = 5;
			y = 28;
			spacingX = 13;
			spacingY = 0;
			cursorX = wherex();
			cursorY = wherey();
			
			do
			{
				prevX = x;
				prevY = y;
				
				textcolor(LIGHTCYAN);
				gotoxy(x, y);
				cout << (char)indicator;
				gotoxy(cursorX, cursorY);
				
				key = getch();
				//! Take key state
				//! Virtual-key codes
				if ((key == 'a' || key == 'A') && (choice-1) > 0)
				{
					choice -= 1;
					x -= spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				else if ((key == 'd' || key == 'D') && (choice+1) <= tolChoice)
				{
					choice += 1;
					x += spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				//! Get ENTER to end loop
				else if (key == (VK_RETURN) )
					isExit = true;
					
			}while(!isExit);
		}
};

class BattleChoice02 : public Indicator
{
	public:
		void moveIndicator()
		{
			isExit = false;
			choice = 1;
			tolChoice = 4;
			x = 12;
			y = 27;
			spacingX = 20;
			spacingY = 1;
			cursorX = wherex();
			cursorY = wherey();
			
			do
			{
				prevX = x;
				prevY = y;
				
				textcolor(LIGHTCYAN);
				gotoxy(x, y);
				cout << (char)indicator;
				gotoxy(cursorX, cursorY);
				
				key = getch();
				//! Take key state
				//! Virtual-key codes
				if ((key == 'a' || key == 'A') && choice != 1 && choice != 3)
				{
					choice -= 1;
					x -= spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				else if ((key == 'd' || key == 'D') && choice != 2 && choice != 4)
				{
					choice += 1;
					x += spacingX;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				if ((key == 'w' || key == 'W') && choice != 1 && choice != 2)
				{
					choice -= 2;
					y -= spacingY;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				else if ((key == 's' || key == 'S') && choice != 3 && choice != 4)
				{
					choice += 2;
					y += spacingY;
					gotoxy(prevX, prevY);
					cout << " ";
				}
				//! Get ENTER to end loop
				else if (key == (VK_RETURN) )
					isExit = true;
					
			}while(!isExit);
		}
};

class Player
{
	public:
		string name;
		string sex[10];
		PLAYER_GENDER gender;
		PLAYER_POSITION position;
		bool met_professor;
		int experience;
		int level;
		int pocketBall;
		int pocketMonster;
		int monsterLeft;
		int x, y;
		int prevX, prevY;
		int cursorX, cursorY;
		
		Player(PLAYER_GENDER gender)
		{
			this->gender = gender;
		}
		
		void initializeStat()
		{
			if (gender == BOY)
			{
				string sex[10] = 
				{
					"      /////////|     ",
					"    /////////|||\\   ",
					"   ///////////||\\\\ ",
					"   \\ __      __  /  ",
					"  (| (o)     (o) |)  ",
					"   |      >      |   ",
					"   | '\\______/`  |  ",
					"    \\___________/   ",
					"        _) (_        ",
					"       / \\_/ \\     "
				};
				for(int i=0; i <10; i++)
				{
					this->sex[i] = sex[i];
				}
				//memcpy(this->sex, sex, sizeof(this->sex));
			}
			else if (gender == GIRL)
			{
				string sex[10] = 
				{
					"                         ",
					"  /////////////\\\\\\\\  ",
					" (((((((((((((( \\\\\\\\ ",
					" ))) ~~      ~~  (((     ",
					" ((( (*)     (*) )))     ",
					" )))     <       (((     ",
					" ((( '\\______/`  )))    ",
					" )))\\___________/(((    ",
					"        _) (_            ",
					"       / \\_/ \\         "
				};
				for(int i=0; i <10; i++)
				{
					this->sex[i] = sex[i];
				}
				//memcpy(this->sex, sex, sizeof(this->sex));
			}
			
			experience = 0;
			level = 1;
			pocketBall = 0;
			pocketMonster = 0;
			monsterLeft = 2;
			met_professor = false;
		}
		
		void drawStat()
		{
			int x = screenWidth*0.7+1;
			int y = screenHeight*0.5+1;
			
			textcolor(LIGHTCYAN);
			gotoxy(x, y);
			cout << "Experience : " <<experience;
			gotoxy(x, y + 2);
			cout << "Level      : " << level;
			gotoxy(x, y + 4);
			cout << "Pocket     : " << pocketBall;
			gotoxy(x, y + 5);
			cout << "Ball";
			gotoxy(x, y + 7);
			cout << "Pocket     : " << pocketMonster; 
			gotoxy(x, y + 8);
			cout << "Monster";
			gotoxy(x, y +10);
			cout << "Monsters   : " << monsterLeft;
			gotoxy(x, y + 11);
			cout << "Left";
		}
		
		void refreshStat()
		{
			if (experience>999)
			{
				level++;
				experience -= 1000;
			}
			
			drawStat();
		}
				
		void initialize(int x, int y)
		{
			this->x = x;
			this->y = y;
			cursorX = wherex();
			cursorY = wherey();
		}
		
		void move_Up()
		{
			bool moved = false;
			char key;
			char prevChar = outdoor->map[y][x];
			prevX = x;
			prevY = y;
			
			do
			{
				key = getch();
				moved = true;
				
				if (key == 'w' || key == 'W')
					y -= 1;
				
				else 
					moved = false;
				
			}while(!moved);
			
			gotoxy(prevX+outdoor->offsetX, prevY+outdoor->offsetY);
			outdoor->colorMap(prevX, prevY);
			cout<<prevChar;
			
			collision();
			draw();
		}
		
		void move_Down()
		{
			bool moved = false;
			char key;
			char prevChar = outdoor->map[y][x];
			prevX = x;
			prevY = y;
			
			do
			{
				key = getch();
				moved = true;
				
				if (key == 's' || key == 'S')
					y += 1;
					
				else 
					moved = false;
					
			}while(!moved);
			
			gotoxy(prevX+outdoor->offsetX, prevY+outdoor->offsetY);
			outdoor->colorMap(prevX, prevY);
			cout<<prevChar;
			
			collision();
			draw();
		}
		
		void move_All()
		{
			bool moved = false;
			char key;
			char prevChar = outdoor->map[y][x];
			prevX = x;
			prevY = y;
			
			do
			{
				key = getch();
				moved = true;
				
				if (key == 'w' || key == 'W')
					y -= 1;
				
				else if (key == 's' || key == 'S')
					y += 1;
					
				else if (key == 'a' || key == 'A')
					x -= 1;
					
				else if (key == 'd' || key == 'D')
					x += 1;
					
				else 
					moved = false;
				
			}while(!moved);
			
			gotoxy(prevX+outdoor->offsetX, prevY+outdoor->offsetY);
			outdoor->colorMap(prevX, prevY);
			cout<<prevChar;
			
			collision();
			draw();
		}
		
		void collision()
		{
			//! Outdoor entrance check
			if (position == OUTDOOR)
			{
				//! House01
				if (x == 14 && y == 16 && met_professor == false)
				{
					draw();
					met_professor = true;
					gameState = MONSTER_SELECTION;
					system("cls");
				}
				else if (outdoor->map[y][x] == (char)grass)
				{
					int chance = rand()% 15+1;
					
					if (chance>=13)
					{
						draw();
						gameState = BATTLE;
						//system("cls");
					}
				}
			}
			//! Indoor exit check
			else if (position == INDOOR)
			{
				//
			}
			
			//! General collision check
			if (outdoor->map[y][x] != (char)space && outdoor->map[y][x] != (char)grass)
			{
				x = prevX;
				y = prevY;
			}
		}
		
		void draw()
		{
			gotoxy(x+outdoor->offsetX, y+outdoor->offsetY);
			if (gender == BOY)
				textcolor(YELLOW);
				
			else if (gender == GIRL)
				textcolor(LIGHTRED);
				
			cout<<(char)hero;
			gotoxy(cursorX, cursorY);
		}
};

Player* player;

class Monster
{
	public:
		string name;
		string art[6];
		int hp;
		int hp_base;
		int recovery;
		int attack;
		int defense;
		int speed;
		int accuracy;
		int special;
		
		virtual void initializeStat() = 0;
};

class Starter : public Monster
{
	public:
		STARTER_MONSTER monster;
		
		Starter(STARTER_MONSTER monster)
		{
			this->monster = monster;
		}
		
		void initializeStat()
		{
			if (monster == EAGGLE)
			{
				name = "EAGGLE";
				
				string art[6] = 
				{
					"     __.   .__         ",
					"    /'(  _  )`\\       ",
					"   / . \\/^\\/ . \\    ",
					"  /  _)_`-'_(_  \\     ",
					" /.-~   ).(   ~-.\\    ",
					"/'     /\\_/\\     `\\ "
					//"       \"-V-\"         "
				};
				for(int i=0; i <6; i++)
					this->art[i] = art[i];
				
				hp = 39;
				hp_base = hp;
				recovery = 6;
				attack = 52;
				defense = 43;
				speed = 65;
				accuracy = 53;
				special = 50;
			}
			else if (monster == SQUILLA)
			{
				name = "SQUILLA";
				
				string art[6] = 
				{
					"      \\/)/)    ",
					"    _'  oo(_.-. ",
					"  /'.     .---' ",
					"/'-./    (      ",
					")     ; __\\    ",
					"\\_.'\\ : __|   "
					//"     )  _/      ",
					//"    (  (,.      ",
					//"     '-.-'      "
				};
				for(int i=0; i <6; i++)
					this->art[i] = art[i];
				
				hp = 44;
				hp_base = hp;
				recovery = 6;
				attack = 48;
				defense = 65;
				speed = 43;
				accuracy = 65;
				special = 50;
			}
			else if (monster == HORNET)
			{
				name = "HORNET";
				
				string art[6] = 
				{
					"  .--.   W   .--.    ",
					" .    , {_} ,    .   ",
					"<     =( X )=      > ",
					" '    `/'''\\`    '  ",
					"  '--'<XXXXX> '--'   ",
					"       <XXX>         "
					//"        <X>          "
				};
				for(int i=0; i <6; i++)
					this->art[i] = art[i];
				
				hp = 45;
				hp_base = hp;
				recovery = 6;
				attack = 49;
				defense = 49;
				speed = 45;
				accuracy = 60;
				special = 65;
			}
		}
};

Starter* starter;

class Enemy : public Monster
{
	public:
		ENEMY_MONSTER monster;
		
		Enemy(ENEMY_MONSTER monster)
		{
			this->monster = monster;
		}
		
		void initializeStat()
		{
			if (monster == LYNX)
			{
				name = "LYNX";
				
				string art[6] =
				{
					"                         ",
					" _._     _,-'\\\"\\\"\\`-._   ",
					"(,-.`._,'(       |]\\`-/|",
					"    `-.-' ]\\ )-`( , o o)",
					"          `-    ]\\`_`''-",
					"                         "
				};
				for(int i=0; i <6; i++)
					this->art[i] = art[i];
					
				hp = 40;
				hp_base = hp;
				recovery = 0;
				attack = 45;
				defense = 35;
				speed = 90;
				accuracy = 51;
				special = 40;
			}
			else if (monster == FRUGG)
			{
				name = "FRUGG";
				
				string art[6] = 
				{
					"       _     _           ",
				    "      (')-=-(')          ",
				    "    __(   ''  )__        ",
				    "   / _/'-----'\\_ \\     ",
				    "___\\\\ \\\\     // //___",
				    ">____)/_\\---/_\\(____<  "
				};
				for(int i=0; i <6; i++)
					this->art[i] = art[i];
					
				hp = 40;
				hp_base = hp;
				recovery = 0;
				attack = 40;
				defense = 35;
				speed = 70;
				accuracy = 53;
				special = 60;
			}
		}
};

Enemy* enemy;

class Box
{
	public:
		int left;
		int right;
		int top;
		int bottom;
		
		virtual void setPosition()
		{
			left = 2;
			right = screenWidth-1;
			top = screenHeight*0.85;
			bottom = screenHeight-1;
			textcolor(CYAN);
			
			drawBox();
		}
		
		void drawBox()
		{
			for(int x=left; x<=right; x++)
			{
				//! Draw top
				gotoxy(x, top);
				if (x==left || x==right) cout<<" ";
				else if (x==left+1 || x==right-1) cout<<",";
				else cout<<"=";
				
				//! Draw both sides
				for(int y=top+1; y<bottom; y++)
				{
					gotoxy(x, y);
					if(x==left || x==left+1 || x==right-1 || x==right) cout<<"|";
					else cout<<" ";
				}
				
				//! Draw bottom
				gotoxy(x, bottom);
				if (x==left || x==right) cout<<" ";
				else if (x==left+1 || x==right-1) cout<<"'";
				else cout<<"=";
			}
		}
		
		virtual void dialogue(int choice)
		{
			int x = left+3;
			int y = top+1;
			
			setPosition();
			textcolor(WHITE);
			gotoxy(x, y);
			switch(choice)
			{
				case 0:
					textcolor(LIGHTRED);
					gotoxy(x, y+1);
					cout << "Move your character with W A S D.";
					break;
					
				case 1:
					for(int i = 0; i < 5; i++)
					{
						textcolor(WHITE);
						gotoxy(x, y);
						if (i == 0)
						{
							cout << "Professor: Hi, " << player->name << "! I'm Professor Ted. Welcome to";
							gotoxy(x, y+1);
							cout << "'Land of Pocket Monster'! This is a dangerous";
							gotoxy(x, y+2);
							cout << "place where wild monsters are everywhere!";
						}
						else if (i == 1)
						{
							cout << "I studied the monsters and helped newcomers like";
							gotoxy(x, y+1);
							cout << "you to get through their first few days here.";
							gotoxy(x, y+2);
							cout << "Most of them like it very much over here.";
						}
						else if (i == 2)
						{
							cout << "All you have to know is that monsters in the wild";
							gotoxy(x, y+1);
							cout << "are dangerous to you, but once you caught them in";
							gotoxy(x, y+2);
							cout << "your pocket, they will turn into a loyal monster to you.";
						}
						else if (i == 3)
						{
							cout << "So, here, before you go out exploring the wild,";
							gotoxy(x, y+1);
							cout << "I have three pocket balls for you to pick. Each";
							gotoxy(x, y+2);
							cout << "pocket ball contains different types of pocket";
						}
						else if (i == 4)
						{
							cout << "monster. Kindly pick one of your type and bring";
							gotoxy(x, y+1);
							cout << "it out to protect against yourself while you";
							gotoxy(x, y+2);
							cout << "explore the wild to catch them all!";
						}
						getch();
						setPosition();
					}
					break;
					
				case 2:
					cout << "Professor: Go out to the wild and find all Pocket Monsters!";
					gotoxy(8, 2);
					cout << "Objective: Find all "<<player->monsterLeft<<" Pocket Monsters.";
					break;
				
				case 3:
					cout << "Little Beet Root Town";
					break;
					
				case 4:
					cout << "Wild " << enemy->name << " appeared!";
					getch();
					setPosition();
					textcolor(WHITE);
					gotoxy(x, y);
					cout << "Go! " << starter->name <<"!";
					getch();
					break;
					
				case 5:
					cout << "What should " << starter->name << " do?";
					gotoxy(x+2, y+2);
					cout << "Fight";
					gotoxy(x+15, y+2);
					cout << "Run";
					gotoxy(x+28, y+2);
					cout << "Pocket Ball";
					break;
					
				case 6:
					cout << "Fight";
					gotoxy(x+9, y+1);
					cout << "Attack";
					gotoxy(x+29, y+1);
					cout << "Recovery";
					gotoxy(x+9, y+2);
					cout << "Block";
					gotoxy(x+29, y+2);
					cout << "Back";
					break;
					
				case 7:
					cout << "Got away safely!";
					getch();
					break;
					
				case 8:
					cout << "Couldn't get away!";
					getch();
					break;
					
				case 9:
					cout << "Awwww!";
					gotoxy(x, y);
					cout << "You are out of Pocket Balls!";
					getch();
					break;
					
				case 10:
					cout << player->name << " used";
					gotoxy(x, y+1);
					cout << "POCKET BALL!";
					getch();
					break;
					
				case 11:
					cout << "Gotcha!";
					gotoxy(x, y+1);
					cout << enemy->name << " was caught!";
					getch();
					break;
					
				case 12:
					cout << "Oh, no!";
					gotoxy(x, y+1);
					cout << "The Pocket Monster broke free!";
					getch();
					break;
					
				case 13:
					cout << starter->name << " used recovery!";
					getch();
					break;
					
				case 14:
					cout << starter->name << " used all its recovery!";
					getch();
					break;
					
				case 15:
					cout << starter->name << " blocked " << enemy->name << "'s next attack!";
					getch();
					break;
					
				case 16:
					cout << starter->name << " failed to block " << enemy->name << "'s next attack!";
					getch();
					break;
					
				case 17:
					cout << starter->name << " used normal attack!";
					getch();
					break;
					
				case 18:
					gotoxy(x, y+1);
					cout << "Critical Hit!";
					break;
					
				case 19:
					cout << "Foe " << enemy->name << " dodged your attack!";
					getch();
					break;
					
				case 20:
					cout << "Foe " << enemy->name << " used normal attack!";
					getch();
					break;
			}
		}
};

Box* dialogbox;

class NameBox : public Box
{
	public:
		void setPosition()
		{
			left = screenWidth*0.7-1;
			right = screenWidth-1;
			top = screenHeight*0.4;
			bottom = top+2;
			textcolor(LIGHTMAGENTA);
			
			drawBox();
			
			textcolor(LIGHTGRAY);
			gotoxy(left+7, top+1);
			cout<<player->name;
		}
};

NameBox* namebox;

class StatBox : public Box
{
	public:
		void setPosition()
		{
			left = screenWidth*0.7-1;
			right = screenWidth-1;
			top = screenHeight*0.5;
			bottom = screenHeight-1;
			textcolor(LIGHTMAGENTA);
			
			drawBox();
			
			player->drawStat();
		}
};

StatBox* statbox;

class PropertyBox : public Box
{
	public:
		void setPosition()
		{
			left = 2;
			right = screenWidth*0.7-2;
			top = screenHeight*0.85;
			bottom = screenHeight-1;
			textcolor(LIGHTMAGENTA);
			
			drawBox();
		}
};

PropertyBox* propertybox;

class MapBox : public Box
{
	public:
		void setPosition()
		{
			left = 2;
			right = screenWidth*0.7-2;
			top = 2;
			bottom = screenHeight*0.85-1;
			textcolor(LIGHTMAGENTA);
			
			drawBox();
		}
};

MapBox* mapbox;

void displayMainMenu()
{	
	gotoxy(1, 5);
	textcolor(YELLOW);
	cout << "            ___       ___       ___       ___       ___       ___              "                  << endl;
	cout << "           /\\  \\     /\\  \\     /\\  \\     /\\__\\     /\\  \\     /\\  \\             "      << endl;
	cout << "          /::\\  \\   /::\\  \\   /::\\  \\   /:/ _/_   /::\\  \\    \\:\\  \\            "       << endl;
	cout << "         /::\\:\\__\\ /:/\\:\\__\\ /:/\\:\\__\\ /::-'\\__\\ /::\\:\\__\\   /::\\__\\           "  << endl;
	cout << "         \\/\\::/  / \\:\\/:/  / \\:\\ \\/__/ \\;:;-',-' \\:\\:\\/  /  /:/\\/__/           "      << endl;
	cout << "            \\/__/   \\::/  /   \\:\\__\\    |:|  |    \\:\\/  /   \\/__/              "          << endl;
	cout << "                     \\/__/     \\/__/     \\|__|     \\/__/                       "              << endl;
	textcolor(LIGHTMAGENTA);
	cout << "        ___       ___       ___       ___       ___       ___       ___    "                      << endl;
	cout << "       /\\__\\     /\\  \\     /\\__\\     /\\  \\     /\\  \\     /\\  \\     /\\  \\   "        << endl;
	cout << "      /::L_L_   /::\\  \\   /:| _|_   /::\\  \\    \\:\\  \\   /::\\  \\   /::\\  \\  "           << endl;
	cout << "     /:/L:\\__\\ /:/\\:\\__\\ /::|/\\__\\ /\\:\\:\\__\\   /::\\__\\ /::\\:\\__\\ /::\\:\\__\\ "   << endl;
	cout << "     \\/_/:/  / \\:\\/:/  / \\/|::/  / \\:\\:\\/__/  /:/\\/__/ \\:\\:\\/  / \\;:::/  / "          << endl;
	cout << "       /:/  /   \\::/  /    |:/  /   \\::/  /   \\/__/     \\:\\/  /   |:\\/__/  "                << endl;
	cout << "       \\/__/     \\/__/     \\/__/     \\/__/               \\/__/     \\|__|   "                << endl;
	textcolor(LIGHTCYAN);
	gotoxy(37, 21);
	cout << " Play" << endl;
	gotoxy(37,23);
	cout << " Exit" << endl;
	textcolor(LIGHTRED);
	gotoxy(31, 27);
	cout<<"W A S D to control.";
	textcolor(LIGHTGREEN);
	gotoxy(29, 28);
	cout << "Press ENTER to select.";
	
	MainMenuIndicator main;
	main.moveIndicator();
	
	if (main.choice == 1)
	{
		gameState = CHARACTER_SELECTION;
		system("CLS");
	}
	else if (main.choice == 2)
	{
		exit(0);
	}
}

void displayCharSel()
{
	//! Draw boy
	string boy[] =
	{
		"     /////////|     ",
		"   /////////|||\\   ",
		"  ///////////||\\\\ ",
		"  \\ __      __  /  ",
		" (| (o)     (o) |)  ",
		"  |      >      |   ",
		"  | '\\______/`  |  ",
		"   \\___________/   ",
		"       _) (_        ",
		"      / \\_/ \\     ",
		"     //     \\\\    ",
		"    // |   | \\\\   ",
		"    \\\\ |___| //   ",
		"     (/     \\)     ",
		"      |__|__|       ",
		"       | | |        ",
		"       | | |        ",
		"      _|_|_|_       ",
		"                    ",
		"                    ",
		"        Boy         "
	};
	//! Print boy
	for(int i=0; i<21; i++)
	{
		gotoxy(13, 3+i);
		if (i < 20)
		{
			textcolor(YELLOW);
			cout << boy[i];
		}
		else
		{
			textcolor(LIGHTCYAN);
			cout << boy[i];
		}
	}
	
	//! Draw girl
	string girl[] = 
	{
		"                         ",
		"  /////////////\\\\\\\\  ",
		" (((((((((((((( \\\\\\\\ ",
		" ))) ~~      ~~  (((     ",
		" ((( (*)     (*) )))     ",
		" )))     <       (((     ",
		" ((( '\\______/`  )))    ",
		" )))\\___________/(((    ",
		"        _) (_            ",
		"       / \\_/ \\         ",
		"      /(     )\\         ",
		"     // )___( \\\\       ",
		"     \\\\(     )//       ",
		"      (       )          ",
		"       |  |  |           ",
		"        | | |            ",
		"        | | |            ",
		"       _|_|_|_           ",
		"                         ",
		"                         ",
		"         Girl            "
	};
	//! Print girl
	for(int i=0; i<21; i++)
	{
		gotoxy(48, 3+i);
		if (i < 20)
		{
			textcolor(LIGHTRED);
			cout << girl[i];
		}
		else
		{
			textcolor(LIGHTCYAN);
			cout << girl[i];
		}
	}
	//! Print dialogue box and ask player to choose gender
	dialogbox = new Box();
	
	dialogbox->setPosition();
	textcolor(WHITE);
	gotoxy(31, 27);
	cout << "Choose your gender.";
	textcolor(LIGHTGREEN);
	gotoxy(29, 28);
	cout << "Press ENTER to select.";
	
	CharSelIndicator character;
	character.moveIndicator();
	
	if (character.choice == 1)
	{
		player = new Player(BOY);
	}
	else if (character.choice == 2)
	{
		player = new Player(GIRL);
	}
	
	//! Clear dialogue box, tell player's gender and ask for name
	dialogbox->setPosition();
	gotoxy(34, 26);
	if (player->gender == BOY)
	{
		textcolor(YELLOW);
		cout << "You're a BOY!";
	}
	else if (player->gender == GIRL)
	{
		textcolor(LIGHTRED);
		cout << "You're a GIRL!";
	}
	
	textcolor(WHITE);
	gotoxy(32, 27);
	cout << "What is your name?";
	gotoxy(35, 28);
	cout << "___________";
	gotoxy(35, 28);
	textcolor(LIGHTGREEN);
	cin >> setw(11) >> player->name;
	player->initializeStat();
	
	gameState = SHOW_GUI;
	system("CLS");
}

void showGUI()
{
	//! Print player gender head
	if(player->gender == BOY) 
		textcolor(YELLOW);
		
	else if (player->gender == GIRL) 
		textcolor(LIGHTRED);
		
	for (int i=0; i<10; i++)
	{
		gotoxy(screenWidth*0.72, 2+i);
		cout << player->sex[i];
	}
	
	//! Draw player's name box
	namebox = new NameBox();
	namebox->setPosition();
	
	//! Draw player's stats box
	statbox = new StatBox();
	statbox->setPosition();
	
	//!Draw small dialog box for information and preperties
	propertybox = new PropertyBox();
	propertybox->setPosition();
	
	//! Draw map box to hold map
	mapbox = new MapBox();
	mapbox->setPosition();
	
	outdoor = new Outdoor();
	outdoor->initializeMap();
	
	outdoor->displayMap();
}

void drawPocketBall(int x, int y)
{
	string ball[] =
	{
		"   @@@@@  ",
		" @@@@@@@@@ ",
	    "||||[0]||||",
	    " OOOOOOOOO ",
	    "   OOOOO  "
  	};
  	
	for(int i = 0; i < 5; i++)
	{
		gotoxy(x, y + i);
		if (i < 2)
		{
			textcolor(LIGHTRED);
			cout << ball[i];
		}
		else if (i == 2)
		{
			textcolor(DARKGRAY);
			cout << ball[i];
		}
		else
		{
			textcolor(WHITE);
			cout << ball[i];
		}
	}
}

void displayMonsSel()
{
	//! Draw Eaggle
	string eaggle[] =
	{
		"     __.   .__         ",
		"    /'(  _  )`\\       ",
		"   / . \\/^\\/ . \\    ",
		"  /  _)_`-'_(_  \\     ",
		" /.-~   ).(   ~-.\\    ",
		"/'     /\\_/\\     `\\ ",
		"       \"-V-\"         "
	};
	//! Print boy
	for(int i=0; i<7; i++)
	{
		gotoxy(9, 5+i);
		textcolor(LIGHTRED);
		cout << eaggle[i];
	}
	
	//! Draw Squilla
	string squilla[] =
	{
		"      \\/)/)    ",
		"    _'  oo(_.-. ",
		"  /'.     .---' ",
		"/'-./    (      ",
		")     ; __\\    ",
		"\\_.'\\ : __|   ",
		"     )  _/      ",
		"    (  (,.      ",
		"     '-.-'      "
	};
	//! Print boy
	for(int i=0; i<9; i++)
	{
		gotoxy(35, 4+i);
		textcolor(LIGHTCYAN);
		cout << squilla[i];
	}
	
	//! Draw Hornet
	string hornet[] =
	{
		"  .--.   W   .--.    ",
		" .    , {_} ,    .   ",
		"<     =( X )=      > ",
		" '    `/'''\\`    '  ",
		"  '--'<XXXXX> '--'   ",
		"       <XXX>         ",
		"        <X>          "
	};
	//! Print boy
	for(int i=0; i<7; i++)
	{
		gotoxy(55, 5+i);
		textcolor(YELLOW);
		cout << hornet[i];
	}
	
	drawPocketBall(13, 12);
	drawPocketBall(36, 12);
	drawPocketBall(59, 12);
	textcolor(LIGHTRED);
	gotoxy(16, 19);
	cout << "Eaggle";
	gotoxy(17, 20);
	cout << "Fire";
	
	textcolor(LIGHTCYAN);
	gotoxy(38, 19);
	cout << "Squilla";
	gotoxy(39, 20);
	cout << "Water";
	
	textcolor(YELLOW);
	gotoxy(62, 19);
	cout << "Hornet";
	gotoxy(62, 20);
	cout << "Grass";
	
	dialogbox->setPosition();
	dialogbox->dialogue(1);	
	
	textcolor(WHITE);
	gotoxy(27 ,26);
	cout << "Choose your Pocket Monster!";
	textcolor(LIGHTGREEN);
	gotoxy(29, 28);
	cout << "Press ENTER to select.";
	
	MonsSelIndicator monster;
	monster.moveIndicator();
	dialogbox->setPosition();
	
	if(monster.choice == 1)
	{
		starter = new Starter(EAGGLE);
		textcolor(WHITE);
		gotoxy(32, 26);
		cout << "You chose Eaggle!";
		gotoxy(28, 27);
		cout << "A fire type Pocket Monster.";
	}	
	else if(monster.choice == 2)
	{
		starter = new Starter(SQUILLA);
		textcolor(WHITE);
		gotoxy(34, 26);
		cout << "You chose Squilla!";
		gotoxy(28, 27);
		cout << "A water type Pocket Monster.";
	}	
	else if(monster.choice == 3)
	{
		starter = new Starter(HORNET);
		textcolor(WHITE);
		gotoxy(34, 26);
		cout << "You chose Hornet!";
		gotoxy(28, 27);
		cout << "A grass type Pocket Monster.";
	}
	textcolor(LIGHTGREEN);
	gotoxy(29, 28);
	cout << "Press any key to continue.";
	getch();
	
	dialogbox->setPosition();
	dialogbox->dialogue(2);
	getch();
	player->pocketBall+=9;
	
	starter->initializeStat();
	gameState = SHOW_GUI;
	system("CLS");
}

void chechWin()
{
	if (player->monsterLeft <= 0)
	{
		system("cls");
		textcolor(WHITE);
		gotoxy(screenWidth/2 - 6, screenHeight/2 - 1);
		cout << "CONGRATULATIONS";
		gotoxy(screenWidth/2 - 15, screenHeight/2);
		cout << "You found all the Pocket Monster!";
		getch();
		gotoxy(screenWidth/2 - 8, screenHeight/2+1);
		cout << "Thanks for playing!";
		gotoxy(1, screenHeight - 3);
		exit(0);
	}
}

void checkLose()
{
	if (starter->hp <= 0)
	{
		// lose game
		system("cls");
		textcolor(WHITE);
		gotoxy(screenWidth/2 - 4, screenHeight/2 - 1);
		cout << "GAME OVER";
		gotoxy(screenWidth/2 - 14, screenHeight/2);
		cout << "You lost your Pocket Monster!";
		gotoxy(screenWidth/2 - 8, screenHeight/2 + 2);
		cout << "To be continued...";
		getch();
		gotoxy(1, screenHeight - 3);
		exit(0);
	}
}

void battle()
{
	bool battling = true;
	bool blocked = false;
	bool dodge = false;
	int escape = 0;
	
	do
	{
		propertybox->dialogue(5);
		BattleChoice01 battle01;
		battle01.moveIndicator();
		
		if (battle01.choice == 1)
		{
			propertybox->setPosition();
			propertybox->dialogue(6);
			BattleChoice02 battle02;
			battle02.moveIndicator();
			
			if (battle02.choice == 1)
			{
				bool criticalHit = false;
			
				// calculating damage
				int damage = round(((float)((2*player->level)+10)/250) * ((float)starter->attack/enemy->defense) * starter->attack + 2);
				float bonus = (float)starter->accuracy/70 * 100;
				int random = rand()%100;
				if (random <= bonus && random >= 50)
				{
					damage += 3;
					criticalHit = true;
				}
				else if (random < 50)
				{
					damage += 2;
					criticalHit = false;
				}
				else if (random > bonus)
				{
					damage += 1;
					criticalHit = false;
				}
				
				if (criticalHit == true) propertybox->dialogue(18);
				propertybox->dialogue(17);
				
				// calculating enemy dodge chances
				int chance = round(((float)enemy->accuracy/100) * enemy->accuracy/starter->speed * 10);
				int randNum = rand()%10;
				if (randNum >= chance && randNum < 7)
				{
					dodge = true;
				}
				else
				{
					dodge = false;
					
					if (damage > 0)
						enemy->hp -= damage;
						
					if (enemy->hp < 0)
						enemy->hp = 0;
				}
			}
			else if (battle02.choice == 2)
			{
				int heal = 10;
				
				if (starter->recovery>0)
				{
					starter->recovery--;
					starter->hp+=heal;
					propertybox->dialogue(13);
				}
				else
				{
					propertybox->dialogue(14);
					continue;
				}
			}
			else if (battle02.choice == 3)
			{
				int chance = round(((float)starter->accuracy/100) * starter->accuracy/enemy->speed * 10);
				int random = rand()%10;
				if (random >= chance && random < 7)
				{
					blocked = true;
					propertybox->dialogue(15);
				}
				else
				{
					blocked = false;
					propertybox->dialogue(16);
				}
			}
			else
			{
				continue;
			}
		}
		else if (battle01.choice == 2)
		{
			int A = starter->speed;
			float B = (float)enemy->speed/4;
			int C = escape;
			float chance = (((A * 32)/B) + 30) * C;
			int random = rand()% 225;
			
			if (random < chance)
			{
				propertybox->dialogue(7); 
				battling = false;
			}
			else if (random >= chance)
			{
				propertybox->dialogue(8); 
				battling = true;
			}
		}
		else
		{
			if (player->pocketBall>0)
			{
				player->pocketBall--;
				player->refreshStat();
				propertybox->dialogue(10);
				
				// calculating the chances to capture
				bool success = false;
				float chance = ((float)enemy->special/110)*10;
				int random = rand()% 10 + 1;
				float bonus = ((float)enemy->hp/enemy->hp_base)*100;
				
				if (bonus < 50) chance -= 1;
				
				if (random > chance)
				{
					success = true;
					
					for(int i = 0; i < 6; i++)
					{
						gotoxy(28, 6 + i);	
						cout << "                         ";
					}
					drawPocketBall(33, 7);
					propertybox->dialogue(11);
					
					if (captured[enemy->monster] == false)
					{
						player->experience += 600;
						player->monsterLeft--;
						captured[enemy->monster] == true;
						chechWin();
					}
					else if (captured[enemy->monster] == true)
					{
						player->experience += 300;
					}
					player->pocketMonster++;
					player->refreshStat();
					battling = false;
				}
				else if (random <= chance)
				{
					success = false;
					propertybox->dialogue(12);
				}
			}
			else
			{
				propertybox->dialogue(9);
			}
		}
		textcolor(WHITE);
		gotoxy(18, 5);
		cout << enemy->hp << " ";
		
		if (enemy->hp<=0)
			battling = false;
		
		//! Enemy attack
		else
		{
			bool criticalHit = false;
			int level = 1;
			
			if (dodge == false)
			{
				// calculating damage
				int damage = round(((float)((2*level)+10)/250) * ((float)enemy->attack/starter->defense) * enemy->attack + 2);
				float bonus = (float)enemy->accuracy/70 * 100;
				int randNum = rand()%100;
				if (randNum <= bonus && randNum >= 50)
				{
					damage += 3;
					criticalHit = true;
				}
				else if (randNum < 50)
				{
					damage += 2;
					criticalHit = false;
				}
				else if (randNum > bonus)
				{
					damage += 1;
					criticalHit = false;
				}
				
				if (blocked == false)
				{
					if (damage > 0)
						starter->hp -= damage;
						
					if (starter->hp < 0)
						starter->hp = 0;
						
					if (criticalHit == true) propertybox->dialogue(18);
					propertybox->dialogue(20);
					
					checkLose();
				}
			}
		}
		
		gotoxy(45, 22);
		cout << starter->hp << " ";
		
	}while(battling == true);
}

void displayBattle()
{
	int random = rand()% 8+1;
	
	if(random<=4)
		enemy = new Enemy(LYNX);
		
	else if(random>4)
		enemy = new Enemy(FRUGG);
	
	enemy->initializeStat();
	
	//! Redraw mapbox to clear away map and show battle
	mapbox->setPosition();
	propertybox->setPosition();
	
	// hp box
	textcolor(DARKGRAY);
	gotoxy(4, 3);
	cout << "  ____________________,";
	gotoxy(4, 4);
	cout << " /                    |";
	gotoxy(4, 5);
	cout << "|                     |";
	gotoxy(4, 6);
	cout << "|____________________/";
	
	gotoxy(30, 20);
	cout << "  ____________________,";
	gotoxy(30, 21);
	cout << " /                    |";
	gotoxy(30, 22);
	cout << "|                     |";
	gotoxy(30, 23);
	cout << "|____________________/";
	
	textcolor(WHITE);
	gotoxy(7, 4);
	cout << enemy->name;
	gotoxy(18, 5);
	cout << enemy->hp << " / " << enemy->hp_base;
	
	gotoxy(34, 21);
	cout << starter->name;
	gotoxy(45, 22);
	cout << starter->hp << " / " << starter->hp_base;
	
	//! Draw enemy monster
	for(int i = 0; i < 6; i++)
	{
		gotoxy(28, 5 + i);
		if (enemy->monster == LYNX)
			textcolor(LIGHTMAGENTA);
			
		else if(enemy->monster == FRUGG)
			textcolor(LIGHTGREEN);
			
		cout << enemy->art[i];
	}
	
	//! Draw player monster
	for(int i = 0; i < 6; i++)
	{
		gotoxy(5, 18 + i);
		if (starter->monster == EAGGLE)
			textcolor(LIGHTRED);
			
		else if(starter->monster == SQUILLA)
			textcolor(LIGHTCYAN);
			
		else if(starter->monster == HORNET)
			textcolor(YELLOW);
			
		cout << starter->art[i];
	}
	
	propertybox->dialogue(4);
	battle();
	
	gameState = SHOW_GUI;
	system("cls");
}

int main()
{
	system("mode con: cols=80 lines=30");
	SetConsoleTitle("Pocket Monster v2");
	srand(time(NULL));
	textcolor(WHITE);
	
	if (gameState == MAIN_MENU)
	{
		displayMainMenu();
		hideCursor();
	}
		
	if (gameState == CHARACTER_SELECTION)
		displayCharSel();

	if (gameState == SHOW_GUI)
	{
		showGUI();
		propertybox->dialogue(0);
	}
	
	player->initialize(14, 17);
	player->position = OUTDOOR;
	player->draw();
	
	do
	{
		player->move_Up();
		
		if (gameState == MONSTER_SELECTION)
			displayMonsSel();
			
		if (gameState == SHOW_GUI)
		{
			showGUI();
			propertybox->dialogue(3);
			player->draw();
		}
		
	}while(!player->met_professor);
	
	bool isExit = false;
	do
	{	
		player->move_All();
		
		if (gameState == BATTLE)
		{
			displayBattle();
			
			if (gameState == SHOW_GUI)
			{
				showGUI();
				propertybox->dialogue(3);
				player->draw();
			}
		}
		
	}while(!isExit);
	
	system("pause");
	return 0;
}
