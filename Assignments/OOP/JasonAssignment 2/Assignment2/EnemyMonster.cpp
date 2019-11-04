#include "DefaultHeaderFiles.h"

using namespace std;

EnemyMonster::EnemyMonster()
{
	mode = "";
}

string EnemyMonster::getMode()
{
	return mode;
}

void EnemyMonster::displayMode()
{
	cout<<mode<<endl;
}
