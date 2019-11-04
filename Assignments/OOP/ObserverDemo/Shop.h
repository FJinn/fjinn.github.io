#pragma once 

#include "IObserver.h"
#include <iostream>
#include <string>

using namespace std;

class Shop : public IObserver
{
	string name;
	float price;
	
	public:
		Shop(string n);
		void Update(float price);
};
