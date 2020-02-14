#ifndef FACTORYINTERFACE_H
#define FACTORYINTERFACE_H

#include "Strategy.h"
#include "Factory.h"
#include "Equipment.h"

class FactoryInterface
{
public:
	//factory
	Factory* itemFac = Factory::createItem(1);
	Factory* clothFac = Factory::createItem(2);
	Factory* totemFac = Factory::createItem(3);
	Factory* pantsFac = Factory::createItem(4);
	Factory* ringFac = Factory::createItem(5);
	Factory* shoesFac = Factory::createItem(6);

	Factory* equipFac = new Factory();
	
	void loadList()
	{
		equipFac->itemList = itemFac->itemList;
		equipFac->clothList = clothFac->clothList;
		equipFac->totemList = totemFac->totemList;
		equipFac->pantsList = pantsFac->pantsList;
		equipFac->ringList = ringFac->ringList;
		equipFac->shoesList = shoesFac->shoesList;
	}

	void displayItem(int x, int y)
	{
		itemFac->displayItem(x, y);
	}
	
	void displayCloth(int x, int y)
	{
		clothFac->displayCloth(x, y);
	}
	
	void displayTotem(int x, int y)
	{
		totemFac->displayTotem(x, y);
	}
	
	void displayPants(int x, int y)
	{
		pantsFac->displayPants(x ,y);
	}
	
	void displayRing(int x, int y)
	{
		ringFac->displayRing(x, y);
	}

	void displayShoes(int x, int y)
	{
		shoesFac->displayShoes(x, y);
	}
	
	// equipFac
	void chooseItem(int choice)
	{
		equipFac->addItem(choice);
	}
	
	void chooseCloth(int choice)
	{
		equipFac->addCloth(choice);
	}
	
	void chooseTotem(int choice)
	{
		equipFac->addTotem(choice);
	}
	
	void choosePants(int choice)
	{
		equipFac->addPants(choice);
	}
	
	void chooseRing(int choice)
	{
		equipFac->addRing(choice);
	}
	
	void chooseShoes(int choice)
	{
		equipFac->addShoes(choice);
	}
	
	void displayEquipment(int x, int y)
	{
		equipFac->displayEquipment(x, y);
	}
	
	int getNum(int index)
	{
		return equipFac->getNum(index);
	}

};

#endif
