#include "Class.h"

Spartan::Spartan()
{
	name = "Spartan Jonathan";
	level = 0;
	strength = 10;
	vitality = 10;
	speed = 0;
	mana = 50;
	hp = strength * vitality;
	CreateEquipment(NanoBlade("Nano Blade", 3, 0, "Weapon", 0));
	CreateEquipment(EnergySword("Energy Sword", 4, 0, "Weapon", 0));
	CreateEquipment(SpartanArmor("Spartan Armor", 0, 4, "Body", 0));
	CreateEquipment(AttackGauntlet("Attack Gauntlet", 5, -5, "Hands", 0));
	CreateEquipment(Madness("Madness", 5, -10, "Legs", 0));
}

Soldier::Soldier()
{
	name = "Soldier Javin";
	level = 0;
	strength = 8;
	vitality = 10;
	speed = 0;
	mana = 100;
	hp = strength * vitality;
	CreateEquipment(N7("N7", 0, 3, "Body", 0));
	CreateEquipment(Specs("Specs", 1, 0, "Legs", 0));
	CreateEquipment(Gauntlet("Gauntlet", 1, 1, "Hands", 0));
	CreateEquipment(Lazada("Lazada", 0, 0, "Boots", 4));
	CreateEquipment(NanoBlade("Nano Blade", 3, 0, "Weapon", 0));
}

Ninja::Ninja()
{
	name = "Ninja Teena";
	level = 0;
	strength = 9;
	vitality = 10;
	speed = 0;
	mana = 150;
	hp = strength * vitality;
	CreateEquipment(MagneticBoots("Magnetic Boots", 0, 0, "Boots", 1));
	CreateEquipment(OmniTool("Omni Tool", 2, 0, "Weapon", 0));
	CreateEquipment(DermalArmor("Dermal Armor", 0, 2, "Body", 0));
	CreateEquipment(CurseGauntlet("Curse Gauntlet", -5, -5, "Hands", 0));
	CreateEquipment(Specs("Specs", 1, 0, "Legs", 0));
}

Archer::Archer()
{
	name = "Archer Javin";
	level = 0;
	strength = 8;
	vitality = 10;
	speed = 0;
	mana = 100;
	hp = strength * vitality;
	CreateEquipment(N7("N7", 0, 3, "Body", 0));
	CreateEquipment(Helmet("Helmet", 0, 1, "Legs", -1));
	CreateEquipment(IronRing("Iron Ring", 2, 0, "Hands", 0));
	CreateEquipment(LightSaber("Light Saber", 5, 0, "Weapon", 0));
	CreateEquipment(Greaves("Greaves", 0, 0, "Boots", 3));
}

Mage::Mage()
{
	name = "Mage Javin";
	level = 0;
	strength = 8;
	vitality = 10;
	speed = 0;
	mana = 100;
	hp = strength * vitality;
	CreateEquipment(N7("N7", 0, 3, "Body", 0));
	CreateEquipment(None("None", 0, 1, "Legs", 1));
	CreateEquipment(IronRing("Iron Ring", 2, 0, "Hands", 0));
	CreateEquipment(LightSaber("Light Saber", 5, 0, "Weapon", 0));
	CreateEquipment(Greaves("Greaves", 0, 0, "Boots", 3));
}
