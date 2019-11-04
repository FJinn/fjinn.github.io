#ifndef LEVELBUILDER_H
#define LEVELBUILDER_H

#include <iostream>
#include <string>

using namespace std;

char plain[5][5] = {
	{'+','-', '-', '-', '-'},
	{'|','-', '-', '-', '|'},
	{'|','-', '-', '-', '|'},
	{'|','-', '-', '-', '|'},
	{'+','-', '-', '-', '-'},
};

class Map
{
public:
char map[5][5];	
};

class Ground
{
public:
	Map* map;
	
	void printMap()
	{
		for(int i=0; i<5; i++)
		{
			for(int j=0; j<5; j++)
			{
				cout<<map->map[i][j];
			}
			cout<<endl;
		}
	}
};

class MapBuilder
{
	public:
		virtual Map* getMap() = 0;
};

class Plains : public MapBuilder
{
	public:
		Map* getMap()
		{
			Map* map = new Map();
			for(int i=0; i<5; i++)
			{
				for(int j=0; j<5; j++)
				{
					map->map[i][j] = plain[i][j];
				}
				cout<<endl;
			}
		}
};

class MapDirector
{
	MapBuilder* builder;
	
	public:
		void setBuilder(MapBuilder newBuilder)
		{
			builder = newBuilder;
		}
		
		Ground* getGround()
		{
			Ground* ground = new Ground();
			ground->map = builder-getMap();
		}
};
#endif
