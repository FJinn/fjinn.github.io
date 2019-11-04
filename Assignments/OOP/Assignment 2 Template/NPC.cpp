#include "DefaultHeaderFiles.h"

using namespace std;


NPC::NPC(string n, string t) : GameObject(n)
{
	type = t;
}

string NPC::getType()
{
	return type;
}

void NPC::displayType()
{
	cout<<type<<endl;
}
