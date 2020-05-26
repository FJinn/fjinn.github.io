#include <iostream>
#include <string>
#include <ctime>
#include "windows.h"

using namespace std;

class Hero{
private:
	int health;
	int level;
	int damage;
public:
	Hero();
	Hero(int h, int l, int d);
	void SetHealth(int h);
	void SetLevel(int l);
	void SetDamage(int d);
	int GetHealth();
	int GetLevel();
	int GetDamage();
	void Attack(Hero h);
	
};
