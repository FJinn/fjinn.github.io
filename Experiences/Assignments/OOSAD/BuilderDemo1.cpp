#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Wheel
{
	public:
		int size;
};

class Engine
{
	public:
		int horsePower;
};

class Body
{
	public:
		string shape;
};

class Battery
{
	public:
		string model;
};

// product/ultimate goal
class Car
{
	public:
		Engine* engine;
		Body* body;
		Wheel* wheel[4];
		Battery* battery;
		
		void Specification()
		{
			cout<<"Engine Horsepower: "<<engine->horsePower<<endl;
			cout<<"Wheel Size: "<<wheel[0]->size<<endl;
		}
};

//! builder super class
class CarBuilder
{
	public:
		virtual Wheel* getWheel()=0;
		virtual Engine* getEngine()=0;
		virtual Body* getBody()=0;
		virtual Battery* getBattery()=0;	
};

class ProtonBuilder : public CarBuilder
{
		Wheel* getWheel()
		{
			Wheel* wheel = new Wheel();
			wheel->size = 22;
			return wheel;
		}
		Engine* getEngine()
		{
			Engine* engine = new Engine();
			engine->horsePower = 2000;
			return engine;
		}
		Body* getBody()
		{
			Body* body = new Body();
			body->shape = "Sedan";
			return body;
		}
		Battery* getBattery()
		{
			Battery* battery = new Battery();
			battery->model = "AAA200";
			return battery;
		}
};

class ToyotaBuilder : public CarBuilder
{
		Wheel* getWheel()
		{
			Wheel* wheel = new Wheel();
			wheel->size = 22;
			return wheel;
		}
		Engine* getEngine()
		{
			Engine* engine = new Engine();
			engine->horsePower = 2200;
			return engine;
		}
		Body* getBody()
		{
			Body* body = new Body();
			body->shape = "SUV";
			return body;
		}
		Battery* getBattery()
		{
			Battery* battery = new Battery();
			battery->model = "AAA250";
			return battery;
		}
};

class Director
{
	protected:
		CarBuilder* cBuilder;
	public: 
		void SetCarBuilder(CarBuilder* newBuilder)
		{
			cBuilder = newBuilder;
		}
		
		Car* getCar()
		{
			Car* car = new Car();
			car->body = cBuilder->getBody();
			car->engine = cBuilder->getEngine();
			car->battery = cBuilder->getBattery();
			car->wheel[0] = cBuilder->getWheel();
			car->wheel[1] = cBuilder->getWheel();
			car->wheel[2] = cBuilder->getWheel();
			car->wheel[3] = cBuilder->getWheel();
			
			return car;
		}
};

int main()
{
	Car* car;
	Director director;
	ProtonBuilder proton;
	ToyotaBuilder toyota;
	
	int option;
	cout<<"1. Proton"<<endl;
	cout<<"2. Toyota"<<endl;
	cout<<"Please select your car manufacturer: ";
	cin>>option;
	if(option ==1)
	{
		director.SetCarBuilder(&proton);
		car = director.getCar();
		car->Specification();
	}
	else if(option ==2)
	{
		director.SetCarBuilder(&toyota);
		car = director.getCar();
		car->Specification();	
	}
	else if(option ==3)
	{
		
	}
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
