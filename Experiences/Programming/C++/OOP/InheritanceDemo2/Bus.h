#ifndef BUS_H
#define BUS_H
#include "Vehicle.h"

class Bus : public Vehicle
{
private:
	string permission;

public:
	Bus()
	{}
	
	Bus(string num, string c, string p) : Vehicle(num, c)
	{
		permission = p;
	}
	
	void SetType(string p)
	{
		permission = p;
	}
	
	string GetType()
	{
		return permission;
	}
	
	// inheritance = function overrider
	string Display()
	{
		return "\nPlate Number: "+plateNum+"\nColor: "+color+"\n" + "\nPermission: "+permission+"\n";
	}		
};

#endif
