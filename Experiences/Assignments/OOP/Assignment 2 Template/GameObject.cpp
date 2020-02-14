##include "DefaultHeaderFiles.h"

GameObject::GameObject(string n)
{
	name = n;
}

string GameObject::getName()
{
	return name;
}

void GameObject::Display()
{
	cout<<name<<endl;
}
