#include <iostream>
#include "windows.h"
#include <string>
#include <typeinfo>

using namespace std;

class A
{
	public:
		virtual const char* f() = 0;
};

class B : public A
{
	const char* f()
	{
		return "B\n";
	}
};

class C : public A
{
	const char* f()
	{
		return "C\n";
	}
};

class D : public A
{
	const char* f()
	{
		return "D\n";
	}
};

class E : public A
{
	const char* f()
	{
		return "E\n";
	}
};

int main()
{
	A* list[] = {new B, new C, new D, new E};
	
	A* p = new C;
	
	for(int i=0; i<4; i++)
	{
		if(typeid(*p) == typeid(*list[i]))
		{
			cout<<list[i]->f();
		}
	}
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
