#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

class Father
{
public:
	string name;
	
	Father(string name)
	{
		this->name = name;
	}	
};

class Mother
{
public:
	string name;
	
	Mother(string name)
	{
		this->name = name;
	}
};

class Child : public Father , public Mother
{
public:
	string name;
	
	Child(string name, string Fname, string Mname) : Father(Fname), Mother(Mname)
	{
		this->name = Father::name + Mother::name + name + "Child";
	}
};

int main()
{
	Child myChild("Anonymous ", "David ", "Sharon ");
	cout<<"Name: "<<myChild.name<<endl;
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
