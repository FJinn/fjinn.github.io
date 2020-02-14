#pragma once

#include <string>

using namespace std;

class Aitem
{
	string name;
	public:
		Aitem(string n) : name(n)
		{}
		string getName()
		{
			return name;
		}	
};

class CellPhone : public Aitem
{
	public:
		CellPhone() : Aitem("CellPhone")
		{}
};

class Car : public Aitem
{
	public:
		Car() : Aitem("Car")
		{}
};

class Laptop : public Aitem
{
	public:
		Laptop() : Aitem("Laptop")
		{}
};

class Allowance : public Aitem
{
	public:
		Allowance() : Aitem("Allowance")
		{}
};

class Insurance : public Aitem
{
	public:
		Insurance() : Aitem("Insurance")
		{}
};

class Girlfriend : public Aitem
{
	public:
		Girlfriend() : Aitem("Girlfriend")
		{}
};
