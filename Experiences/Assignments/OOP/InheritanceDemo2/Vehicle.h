#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <string>

using namespace std;

class Vehicle
{
protected:
	string plateNum;
	string color;

public:
	Vehicle()
	{}
	
	Vehicle(string num, string c)
	{
		plateNum = num;
		color = c;
	}		
	
	string Display()
	{
		return "\nPlate Number: " +plateNum+"\nColor: "+color+"\n";
	}
};

#endif
