#include "DefaultHeaderFiles.h"
using namespace std;

NPC::NPC()
{
	type = "";
}

string NPC::getType()
{
	return type;
}

void NPC::displayType()
{
	cout<<type<<endl;
}
