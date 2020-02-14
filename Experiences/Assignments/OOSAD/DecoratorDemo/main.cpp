#include <iostream>
#include "Decorator.h"

using namespace std;

int main(int argc, char** argv) {
	int choice = 0;
	cout<<"========================"<<endl;
	cout<<"++++++Sandwich Menu+++++"<<endl;
	cout<<"========================"<<endl;
	cout<<"Choose your Bread: "<<endl;
	cout<<"1. Wheat Bread"<<endl;
	cout<<"2. Whole Grain"<<endl;
	cout<<"3. Italian"<<endl;
	cout<<endl<<"Your order: ";
	cin>>choice;
	cout<<endl<<endl;
	int topping;
	cout<<"Select Your Topping: "<<endl;
	cout<<"1. Cheese"<<endl;
	cout<<"2. Veg"<<endl;
	cout<<"3. Sauce"<<endl;
	cin>>topping;
	
	Sandwich* sandwich;
	
	switch(choice)
	{
		case 1:
			if(topping == 1)
			{
				sandwich = new CheeseDecorator(new SubDecorator(new WheatBread()));
			}
			else if(topping == 2)
			{
				sandwich = new VegDecorator(new SubDecorator(new WheatBread()));	
			}
			else if(topping == 3)
			{
				sandwich = new SauceDecorator(new SubDecorator(new WheatBread()));	
			}
			break;
		case 2:
			if(topping == 1)
			{
				sandwich = new CheeseDecorator(new SubDecorator(new WholeGrainBread()));
			}
			else if(topping == 2)
			{
				sandwich = new VegDecorator(new SubDecorator(new WholeGrainBread()));	
			}
			else if(topping == 3)
			{
				sandwich = new SauceDecorator(new SubDecorator(new WholeGrainBread()));	
			}
			break;
		case 3:
			if(topping == 1)
			{
				sandwich = new CheeseDecorator(new SubDecorator(new ItalianBread()));
			}
			else if(topping == 2)
			{
				sandwich = new VegDecorator(new SubDecorator(new ItalianBread()));	
			}
			else if(topping == 3)
			{
				sandwich = new SauceDecorator(new SubDecorator(new ItalianBread()));	
			}
			break;
		default:
			break;
	}
	cout<<"Your Order: "<<sandwich->getDesc()<<endl;
	cout<<"Your Price: "<<sandwich->getCost()<<endl;
	cout<<endl;
	
	system("PAUSE");
	
	return 0;
}
