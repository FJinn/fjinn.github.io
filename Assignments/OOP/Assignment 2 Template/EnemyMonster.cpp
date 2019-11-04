#include "DefaultHeaderFiles.h"

using namespace std;

EnemyMonster::EnemyMonster(string n, string t, m) : NPC(n, t)
{
	mode = m;
}

string EnemyMonster::getMode()
{
	return mode;
}

void EnemyMonster::displayMode()
{
	cout<<mode<<endl;
}
