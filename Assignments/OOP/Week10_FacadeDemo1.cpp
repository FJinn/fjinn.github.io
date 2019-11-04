#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Engine
{
	public: 
		void start()
		{
			cout<<"Start"<<endl;
		}
};

class HeadLight
{
	public:
		void turn_on()
		{
			cout<<"Turn On"<<endl;
		}
};

class Car
{
	protected:
		Engine myEngine;
		HeadLight myHeadLight;
	public:
		virtual void turn_ignition_key_on() = 0;
};

class BMW:public Car
{
	public:
		void turn_ignition_key_on()
		{
			myEngine.start();
			myHeadLight.turn_on();
		}
};

class Proton : public Car
{
	public:
		void turn_ignition_key_on()
		{
			myEngine.start();
		}
};

int main()
{
	Proton saga;
	saga.turn_ignition_key_on();
	
	BMW i320;
	i320.turn_ignition_key_on();
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
