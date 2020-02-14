#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <string>
#include <vector>
#include "Equipment.h"

using namespace std;

// factory
class Factory
{
	public:
		vector<Item*> itemList;
		vector<Cloth*> clothList;
		vector<Totem*> totemList;
		vector<Pants*> pantsList;
		vector<Ring*> ringList;
		vector<Shoes*> shoesList;
		
		vector<Equipment*> equipList;
		
		void displayEquipment(int x, int y)
		{
			for(int i=0; i<equipList.size(); i++)
			{
				gotoxy(x, y+i);
				cout<<equipList[i]->getName();
			}
		}
		
		int getNum(int index)
		{
			index -= 1;
			return equipList[index]->getNum();
		}
		
		// display particular list
		void displayItem(int x, int y)
		{
			for(int i=0; i<itemList.size(); i++)
			{
				gotoxy(x, y+i);
				cout<<itemList[i]->getName();
			}
		}
		
		void displayCloth(int x, int y)
		{
			for(int i=0; i<clothList.size(); i++)
			{
				gotoxy(x, y+i);
				cout<<clothList[i]->getName();
			}
		}
		
		void displayTotem(int x, int y)
		{
			for(int i=0; i<totemList.size(); i++)
			{
				gotoxy(x, y+i);
				cout<<totemList[i]->getName();
			}
		}
		
		void displayPants(int x, int y)
		{
			for(int i=0; i<pantsList.size(); i++)
			{
				gotoxy(x, y+i);
				cout<<pantsList[i]->getName();
			}
		}
		
		void displayRing(int x, int y)
		{
			for(int i=0; i<ringList.size(); i++)
			{
				gotoxy(x, y+i);
				cout<<ringList[i]->getName();
			}
			
		}
		void displayShoes(int x, int y)
		{
			for(int i=0; i<shoesList.size(); i++)
			{
				gotoxy(x, y+i);
				cout<<shoesList[i]->getName();
			}
		}
		
		// add equipment to equipList
		void addItem(int choice)
		{
			equipList.push_back(itemList[choice-1]->getThis());
		}
		
		void addCloth(int choice)
		{
			equipList.push_back(clothList[choice-1]->getThis());
		}
		
		void addTotem(int choice)
		{
			equipList.push_back(totemList[choice-1]->getThis());
		}
		
		void addPants(int choice)
		{
			equipList.push_back(pantsList[choice-1]->getThis());
		}
		
		void addRing(int choice)
		{
			equipList.push_back(ringList[choice-1]->getThis());
		}
		
		void addShoes(int choice)
		{
			equipList.push_back(shoesList[choice-1]->getThis());
		}
		
		// factory pattern
		static Factory* createItem(int index);
};

class ItemFactory : public Factory
{
	public:
		ItemFactory()
		{
			itemList.push_back(new NormalLighter());
			itemList.push_back(new BrokenLighter());
			itemList.push_back(new ExpensiveLighter());
			itemList.push_back(new PlatinumLighter());
		}
};

class ClothFactory : public Factory
{
	public:
		ClothFactory()
		{
			clothList.push_back(new MuddyTunic());
			clothList.push_back(new ItchyTshirt());
			clothList.push_back(new BaggyHoodie());
			clothList.push_back(new TornShirt());
		}
};

class TotemFactory : public Factory
{
	public:
		TotemFactory()
		{
			totemList.push_back(new BearTotem());
			totemList.push_back(new LionTotem());
			totemList.push_back(new RabbitTotem());
			totemList.push_back(new SkullTotem());
		}
};

class PantsFactory : public Factory
{
	public:
		PantsFactory()
		{
			pantsList.push_back(new ShortPants());
			pantsList.push_back(new LongPants());
			pantsList.push_back(new Underwear());
			pantsList.push_back(new Skirt());
		}
};

class RingFactory : public Factory
{
	public:
		RingFactory()
		{
			ringList.push_back(new RuleThemAll());
			ringList.push_back(new EngagementRing());
			ringList.push_back(new WeddingRing());
			ringList.push_back(new CurseRing());
		}
};

class ShoesFactory : public Factory
{
	public:
		ShoesFactory()
		{
			shoesList.push_back(new Sandals());
			shoesList.push_back(new SportShoes());
			shoesList.push_back(new Socks());
			shoesList.push_back(new HikingShoes());
		}
};

Factory* Factory::createItem(int index)
{
	if(index == 1)
	{
		return new ItemFactory();
	}
	else if (index == 2)
	{
		return new ClothFactory();
	}
	else if (index == 3)
	{
		return new TotemFactory();
	}
	else if (index == 4)
	{
		return new PantsFactory();
	}
	else if (index == 5)
	{
		return new RingFactory();
	}
	else if (index == 6)
	{
		return new ShoesFactory();
	}
}

#endif
