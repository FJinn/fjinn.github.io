#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
#include <string>

using namespace std;

class Equipment
{
	private:
		string name;
		int num;
	public:
		Equipment(string s , int n)
		{
			name = s;
			num = n;
		}
		int getNum()
		{
			return num;
		}
		
		Equipment* getThis()
		{
			return this;
		}
		
		string getName()
		{
			return name;
		}	
};

// item
class Item : public Equipment
{
	public:
		Item(string s , int n) : Equipment(s, n)
		{}
};

class NormalLighter : public Item
{
	public:
		NormalLighter() : Item("1. Normal Lighter", 0)
		{}
};
class BrokenLighter : public Item
{
	public:
		BrokenLighter() : Item("2. Broken Lighter", -1)
		{}
};
class ExpensiveLighter : public Item
{
	public:
		ExpensiveLighter() : Item("3. Expensive Lighter", 1)
		{}
};
class PlatinumLighter : public Item
{
	public:
		PlatinumLighter() : Item("4. Platinum Lighter", 2)
		{}
};

// cloth
class Cloth : public Equipment
{
	public:
		Cloth(string s , int n) : Equipment(s, n)
		{}
};

class MuddyTunic : public Cloth
{
	public:
		MuddyTunic() : Cloth("1. Muddy Tunic", 2)
		{}
};
class ItchyTshirt : public Cloth
{
	public:
		ItchyTshirt() : Cloth("2. Itchy Tshirt", 1)
		{}
};
class BaggyHoodie : public Cloth
{
	public:
		BaggyHoodie() : Cloth("3. Baggy Hoodie", 4)
		{}
};
class TornShirt : public Cloth
{
	public:
		TornShirt() : Cloth("4. Torn Shirt", 2)
		{}
};

//totem
class Totem : public Equipment
{
	public:
		Totem(string s , int n) : Equipment(s, n)
		{}
};

class BearTotem : public Totem
{
	public:
		BearTotem() : Totem("1. Bear Totem", 2)
		{}
};
class LionTotem : public Totem
{
	public:
		LionTotem() : Totem("2. Lion Totem", 3)
		{}
};
class RabbitTotem : public Totem
{
	public:
		RabbitTotem() : Totem("3. Rabbit Totem", 1)
		{}
};
class SkullTotem : public Totem
{
	public:
		SkullTotem() : Totem("4. Skull Totem", 4)
		{}
};

//pants
class Pants : public Equipment
{
	public:
		Pants(string s , int n) : Equipment(s, n)
		{}
};

class ShortPants : public Pants
{
	public:
		ShortPants() : Pants("1. Short Pants", 2)
		{}
};
class LongPants : public Pants
{
	public:
		LongPants() : Pants("2. Long Pants", 3)
		{}
};
class Underwear : public Pants
{
	public:
		Underwear() : Pants("3. Underwear", 1)
		{}
};
class Skirt : public Pants
{
	public:
		Skirt() : Pants("4. Skirt", 1)
		{}
};

//ring
class Ring : public Equipment
{
	public:
		Ring(string s , int n) : Equipment(s, n)
		{}
};

class RuleThemAll : public Ring
{
	public:
		RuleThemAll() : Ring("1. Rule Them All", 3)
		{}
};
class EngagementRing : public Ring
{
	public:
		EngagementRing() : Ring("2. Engagement Ring", 4)
		{}
};
class WeddingRing : public Ring
{
	public:
		WeddingRing() : Ring("3. WeddingRing", 2)
		{}
};
class CurseRing : public Ring
{
	public:
		CurseRing() : Ring("4. Curse Ring", 1)
		{}
};

// shoes
class Shoes : public Equipment
{
	public:
		Shoes(string s , int n) : Equipment(s, n)
		{}
};

class Sandals : public Shoes
{
	public:
		Sandals() : Shoes("1. Sandals", 1)
		{}
};
class SportShoes : public Shoes
{
	public:
		SportShoes() : Shoes("2. Sport Shoes", 2)
		{}
};
class Socks : public Shoes
{
	public:
		Socks() : Shoes("3. Socks", 1)
		{}
};
class HikingShoes : public Shoes
{
	public:
		HikingShoes() : Shoes("4. Hiking Shoes", 3)
		{}
};

#endif
