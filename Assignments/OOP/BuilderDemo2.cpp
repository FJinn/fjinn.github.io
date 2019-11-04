#include <iostream>
#include <string>
#include "windows.h"

using namespace std;

class Pizza
{
	private:
		string dough;
		string sauce;
		string topping;
	public:
		void setDough(string d)
		{
			dough = d;
		}
		void setSauce(string s)
		{
			sauce = s;
		}
		void setTopping(string t)
		{
			topping = t;
		}
		
		void DisplayPizza()
		{
			cout<<"Dough: "<<dough<<endl;
			cout<<"Sauce: "<<sauce<<endl;
			cout<<"Topping: "<<topping<<endl;
		}
};

class PizzaBuilder
{
	protected:
		Pizza* pizza;
	public:
		Pizza* getPizza()
		{
			return pizza;
		}
		void CreateNewPizza()
		{
			pizza = new Pizza;
		}
		virtual void BuilderDough()=0;
		virtual void BuilderSauce()=0;
		virtual void BuilderTopping()=0;
};

class MamakPizzaBuilder : public PizzaBuilder
{
	public:
		void BuilderDough()
		{
			pizza->setDough("Naan");
		}
		void BuilderSauce()
		{
			pizza->setSauce("Curry");
		}
		void BuilderTopping()
		{
			pizza->setTopping("Cheese");
		}
};

class JavinPizzaBuilder : public PizzaBuilder
{
	public:
		void BuilderDough()
		{
			pizza->setDough("Tissue");
		}
		void BuilderSauce()
		{
			pizza->setSauce("Special Protein Sauce");
		}
		void BuilderTopping()
		{
			pizza->setTopping("Little Blue");
		}
};

// director class
class Cook
{
	private:
		PizzaBuilder* pizzaBuilder;
	public:
		void SetPizzaBuilder(PizzaBuilder* pb)
		{
			pizzaBuilder = pb;
		}
		Pizza* getPizzaBuilder()
		{
			return pizzaBuilder->getPizza();
		}
		void cookPizza()
		{
			pizzaBuilder->CreateNewPizza();
			pizzaBuilder->BuilderDough();
			pizzaBuilder->BuilderSauce();
			pizzaBuilder->BuilderTopping();
		}
};

int main()
{
	int choice =0;
	PizzaBuilder* pizzaBuilder;
	cout<<"Pizza Menu"<<endl;
	cout<<"1. Mamak Pizza"<<endl;
	cout<<"2. Javin Pizza"<<endl;
	cout<<"Choice: ";
	cin>>choice;
	if(choice ==1)
	{
		pizzaBuilder = new MamakPizzaBuilder();
		cout<<"Mamak Pizza!"<<endl;
	}
	else if(choice ==2)
	{
		pizzaBuilder = new JavinPizzaBuilder();
		cout<<"Javin Pizza!"<<endl;
	}
	
	//! director cook class -> cook object
	Cook cook;
	cook.SetPizzaBuilder(pizzaBuilder);
	cook.cookPizza();
	Pizza* thePizza = cook.getPizzaBuilder();
	thePizza->DisplayPizza();
	
	cout<<endl;
	system("PAUSE");
	return 0;
}
