#ifndef Decorator_H
#define Decorator_H

#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

class Sandwich
{
	public:
		virtual double getCost() = 0;
		virtual string getDesc() = 0;
};

class WheatBread: public Sandwich
{
	public:
		double getCost()
		{
			return 3.5;
		}
		
		string getDesc()
		{
			return "Wheat Bread";
		}
};

class WholeGrainBread: public Sandwich
{
	public:
		double getCost()
		{
			return 4.0;
		}
		
		string getDesc()
		{
			return "Whole Grain Bread";
		}
};

class ItalianBread: public Sandwich
{
	public:
		double getCost()
		{
			return 4.5;
		}
		
		string getDesc()
		{
			return "Italian Bread";
		}
};

class SubDecorator : public Sandwich
{
	protected:
		Sandwich* sandwich;
	public:
		SubDecorator(Sandwich* sandwichRef)
		{
			sandwich = sandwichRef;
		}
		double getCost()
		{
			return sandwich->getCost();
		}
		
		string getDesc()
		{
			return sandwich->getDesc();
		}
};

class CheeseDecorator : public SubDecorator
{
	private:
		double cheeseCost;
		string cheese_Desc()
		{
			return " + Cheese";  
		}
	public:
		CheeseDecorator(Sandwich* ref) : SubDecorator(ref)
		{
			cheeseCost = 3.0;
		}
		
		string getDesc()
		{
			return SubDecorator::getDesc().append(cheese_Desc());
		}
		double getCost()
		{
			return SubDecorator::getCost() + cheeseCost;
		}	
};

class VegDecorator : public SubDecorator
{
	private:
		double VegCost;
		string Veg_Desc()
		{
			return " + Veg";  
		}
	public:
		VegDecorator(Sandwich* ref) : SubDecorator(ref)
		{
			VegCost = 3.5;
		}
		
		string getDesc()
		{
			return SubDecorator::getDesc().append(Veg_Desc());
		}
		double getCost()
		{
			return SubDecorator::getCost() + VegCost;
		}	
};

class SauceDecorator : public SubDecorator
{
	private:
		double SauceCost;
		string Sauce_Desc()
		{
			return " + Sauce";  
		}
	public:
		SauceDecorator(Sandwich* ref) : SubDecorator(ref)
		{
			SauceCost = 3.5;
		}
		
		string getDesc()
		{
			return SubDecorator::getDesc().append(Sauce_Desc());
		}
		double getCost()
		{
			return SubDecorator::getCost() + SauceCost;
		}	
};

#endif
