#include "DefaultHeaderFiles.h"

GameObject::GameObject()
{
	name = "";
}

string GameObject::getName()
{
	return name;
}

void GameObject::Display()
{
	cout<<name<<endl;
}
