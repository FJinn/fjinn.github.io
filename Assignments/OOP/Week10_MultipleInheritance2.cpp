#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

class GrandParent
{
public:
	string name;
	GrandParent(string name)
	{
		this->name = name;
	}
};

class Parent : public GrandParent
{
	public:
		Parent(string name) : GrandParent(name)
		{
			this->name += "Parent";
		}
};

class Child : public Parent 
{
	public:
		Child(string name) : Parent(name)
		{
			this->name += "Child";
		}
};

int main()
{
	Child myChild("David");
	cout<<"Name: "<<myChild.name<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
