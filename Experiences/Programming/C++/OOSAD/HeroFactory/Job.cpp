#include "Job.h"

Warrior::Warrior()
{
	WeaponList(Sword());
	ArmorList(StainedShirt());
	ArmorList(Glove());
	ArmorList(ShortPants());
}

Archer::Archer()
{
	WeaponList(Bow());
	WeaponList(Dagger());
	ArmorList(StainedShirt());
	ArmorList(Glove());
	ArmorList(ShortPants());
}

Mage::Mage()
{
	WeaponList(Wand());
	ArmorList(StainedShirt());
	ArmorList(ClownHat());
	ArmorList(ShortPants());
}
