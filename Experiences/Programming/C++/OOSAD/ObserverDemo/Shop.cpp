// shop is concrete observer
#include "Shop.h"

Shop::Shop(string n)
{
	this->name = n;
}

void Shop::Update(float price)
{
	this->price = price;
	cout<<"Price at "<<name<<" is now "<<price<<endl;
}
