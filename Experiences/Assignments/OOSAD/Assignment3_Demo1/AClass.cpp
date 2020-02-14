#include "AClass.h"
#include "Item.h"
#include "Class.h"

AClass* CreateClass(int choice)
{
	if(choice == 1)
	{
		return new Spartan();
	}
	else if(choice == 2)
	{
		return new Soldier();
	}
	else if(choice == 3)
	{
		return new Ninja();
	}
	else if(choice == 4)
	{
		return new Archer();
	}
	else if(choice == 5)
	{
		return new Mage();
	}
}

void AClass::CreateEquipment(Item item)
{
	equipment.push_back(item);
}

void AClass::PrintEquipment()
{
	for(vector<Item>::iterator iter = equipment.begin(); iter!= equipment.end(); iter++)
	{
		if((*iter).getType() == "Body")
		{
			cout<< "Body: "<<(*iter).getName()<<endl;
		}
		else if((*iter).getType() == "Weapon")
		{
			cout<< "Weapon: "<<(*iter).getName()<<endl;
		}
		else if((*iter).getType() == "Boots")
		{
			cout<< "Boots: "<<(*iter).getName()<<endl;
		}
		else if((*iter).getType() == "Hands")
		{
			cout<< "Hands: "<<(*iter).getName()<<endl;
		}
		else if((*iter).getType() == "Legs")
		{
			cout<< "Legs: "<<(*iter).getName()<<endl;
		}
	}
}

void AClass::ChangeEquiment(int choice, string type)
{
	for(vector<Item>::iterator iter = equipment.begin(); iter!= equipment.end(); iter++)
	{
		if(type == "Weapon")
		{
			if((*iter).getType()==type)
			{
				equipment.erase(iter);
				if(choice == 1)
				{
					CreateEquipment(NanoBlade("Nano Blade", 3, 0, "Weapon", 0));
				}
				else if(choice == 2)
				{
					CreateEquipment(EnergySword("Energy Sword", 4, 0, "Weapon", 0));
				}
				else if(choice == 3)
				{
					CreateEquipment(OmniTool("Omni Tool", 2, 0, "Weapon", 0));
				}
				else if(choice == 4)
				{
					CreateEquipment(LightSaber("Light Saber", 5, 0, "Weapon", 0));
				}
			}
		}
		else if(type == "Body")
		{
			if((*iter).getType()==type)
			{
				equipment.erase(iter);
				if(choice == 1)
				{
					CreateEquipment(DermalArmor("Dermal Armor", 0, 2, "Body", 0));
				}
				else if(choice == 2)
				{
					CreateEquipment(SpartanArmor("Spartan Armor", 0, 4, "Body", 0));
				}
				else if(choice == 3)
				{
					CreateEquipment(N7("N7", 0, 3, "Body", 0));
				}
				else if(choice == 4)
				{
					CreateEquipment(AthenaArmor("Athena Armor", 0, 5, "Body", 0));
				}
			}
		}
		else if(type == "Boots")
		{
			if((*iter).getType()==type)
			{
				equipment.erase(iter);
				if(choice == 1)
				{
					CreateEquipment(HermesBoots("Hermes Boots", 0, 0, "Boots", 2));
				}
				else if(choice == 2)
				{
					CreateEquipment(MagneticBoots("Magnetic Boots", 0, 0, "Boots", 1));
				}
				else if(choice == 3)
				{
					CreateEquipment(Greaves("Greaves", 0, 0, "Boots", 3));
				}
				else if(choice == 4)
				{
					CreateEquipment(Lazada("Lazada", 0, 0, "Boots", 4));
				}
			}
		}
		else if(type == "Hands")
		{
			if((*iter).getType()==type)
			{
				equipment.erase(iter);
				if(choice == 1)
				{
					CreateEquipment(IronRing("Iron Ring", 2, 0, "Hands", 0));
				}
				else if(choice == 2)
				{
					CreateEquipment(Gauntlet("Gauntlet", 1, 1, "Hands", 0));
				}
				else if(choice == 3)
				{
					CreateEquipment(CurseGauntlet("Curse Gauntlet", -5, -5, "Hands", 0));
				}
				else if(choice == 4)
				{
					CreateEquipment(AttackGauntlet("Attack Gauntlet", 5, -5, "Hands", 0));
				}
			}
		}
		else if(type == "Legs")
		{
			if((*iter).getType()==type)
			{
				equipment.erase(iter);
				if(choice == 1)
				{
					CreateEquipment(Helmet("Helmet", 0, 1, "Legs", -1));
				}
				else if(choice == 2)
				{
					CreateEquipment(Specs("Specs", 1, 0, "Legs", 0));
				}
				else if(choice == 3)
				{
					CreateEquipment(None("None", 0, 1, "Legs", 1));
				}
				else if(choice == 4)
				{
					CreateEquipment(Madness("Madness", 5, -10, "Legs", 0));
				}
			}
		}
	}
}

void AClass::LevelUp()
{
	strength += 2;
	vitality += 2;
	hp = strength * vitality;
	mana += 50;
	level++;
}

string AClass::getName()
{
	return name;
}

int AClass::getHP()
{
	return hp;
}

int AClass::getStr()
{
	return strength;
}

int AClass::getVit()
{
	return vitality;
}

int AClass::getLvl()
{
	return level;
}

int AClass::getSpd()
{
	return speed;
}

int AClass::getMP()
{
	return mana;
}

void AClass::performBehaviour()
{
	behaviour->behaviour(name);
}

void AClass::SetBehaviour(Behaviour* behave)
{
	behaviour = behave;
}

