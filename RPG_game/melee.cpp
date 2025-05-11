#include "melee.h"

using namespace std;

Melee::Melee(string name, unsigned damage, unsigned durability)
	: Weapon(name, damage), durability(durability), maxDurability(durability), sharpness(100.0)
{}

Melee::~Melee()
{
}

unsigned Melee::getSharpness() const
{
	return sharpness;
}

unsigned Melee::getDamage() const
{
	return damage*sharpness/100.0;
}

void Melee::use()
{
	if (!isBroken()) 
	{
		durability--;
		unsigned trueDamage = damage*sharpness/100.0;
		sharpness -= 5;
		cout << name << " used successfully!" << endl;
		cout << trueDamage << " damage dealt with: " << name << endl;
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
	sharpness = 100.0;
	if (!isFullyRepaired())
	{
		durability = maxDurability;
		cout << name << " repaired successfully!" << endl;
	}
	else
	{
		cout << name << " is not broken and does not need repair!" << endl;
	}
}
