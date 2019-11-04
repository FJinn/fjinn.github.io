#pragma once
#include "HeroFactory.h"

class Warrior : public HeroFactory
{
	public:
		Warrior();
};

class Archer : public HeroFactory
{
	public:
		Archer();
};

class Mage : public HeroFactory
{
	public:
		Mage();
};
