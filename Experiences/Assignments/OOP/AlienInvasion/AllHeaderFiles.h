#ifndef ALL_HEADER_FILES_H
#define ALL_HEADER_FILES_H

#include <iostream>
#include <fstream>
#include "windows.h"
#include <vector>
#include <string>
#include <ctime>

using namespace std;

#define BOUNDARY_LEFT 5
#define BOUNDARY_RIGHT 55
#define BOUNDARY_TOP 2
#define BOUNDARY_BOTTOM 40

#define MAX_BULLET 5
#define MAX_ENEMY 5
#define ENEMY_SPAWN_DURATION 60

typedef enum
{
	NORMAL, 
	ENEMY01,
	ENEMY02,
	ENEMY03,
	ENEMY04,
	BOSS,
	TOTAL_ENEMY_TYPE
}ENEMY_TYPE;

typedef enum
{
	STRAIGHT, 
	DUO,
	TRIPLE,
	LASER,
	ZIGZAG,
	BOMB,
	STAR,
	TOTAL_BULLET_TYPE
}BULLET_TYPE;

typedef enum
{
	HEALTH_PACK, 
	DUO_PACK,
	TRIPLE_PACK,
	LASER_PACK,
	ZIGZAG_PACK,
	STAR_PACK,
	BOMB_PACK,
	TOTAL_ITEM_TYPE
}ITEM_TYPE;

typedef enum
{
	NORTH = 0,
	EAST,
	WEST,
	SOUTH,
	NORTH_EAST,
	NORTH_WEST,
	SOUTH_EAST,
	SOUTH_WEST,
}DIRECTION;

struct MoveInfo
{
	DIRECTION direction;
	int time;
	bool isCompleted;
};

struct SpawnInfo
{
	ENEMY_TYPE type;
	int time;
	bool isSpawned;
};

extern "C" class Enemy;

//! include custom class header file

#include "conio_yp.h"
#include "GameObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"

#endif
