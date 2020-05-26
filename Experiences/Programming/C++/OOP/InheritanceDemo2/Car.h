#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"

class Car : public Vehicle
{
private:
	string type;

public:
	Car()
	{}
	
	Car(string num, string c, string t) : Vehicle(num, c)
	{
		type = t;
	}
	
	void SetType(string t)
	{
		type = t;
	}
	
	string GetType()
	{
		return type;
	}
	
	// inheritance = function overrider
	string Display()
	{
		return "\nPlate Number: "+plateNum+"\nColor: "+color+"\n" + "\nType: "+type+"\n";
	}		
};

#endif
