#include "melee.h"

using namespace std;

Melee::Melee(string name, unsigned damage, unsigned durability)
	: Weapon(name, damage), durability(durability), maxDurability(durability)
{}

Melee::~Melee()
{
}

void Melee::use()
{
	if (!isBroken()) 
	{
		durability--;
		cout << "Using " << getName() << " with damage: " << getDamage() << endl;
	}
	else 
	{
		cout << name << " is broken and cannot be used!" << endl;
	}
}

unsigned Melee::getDurability() const
{
	return durability;
}

unsigned Melee::getMaxDurability() const
{
	return maxDurability;
}

bool Melee::isBroken() const
{
	return durability==0;
}

bool Melee::isFullyRepaired() const
{
	return durability==maxDurability;
}

void Melee::repair()
{
	if (!isFullyRepaired())
	{
		durability = maxDurability;
	}
	else
	{
		cout << name << " does not need any repair!" << endl;
	}
}
