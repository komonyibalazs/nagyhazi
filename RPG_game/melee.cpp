#include "melee.h"

Melee::Melee(std::string name, unsigned damage, unsigned durability) : Weapon(name, damage), Repairable(durability), sharpness(100.0)
{}

Melee::~Melee()
{
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
		std::cout << name << " used successfully!" << std::endl;
		std::cout << trueDamage << " damage dealt with: " << name << std::endl;
	}
	else 
	{
		std::cout << name << " is broken and cannot be used!" << std::endl;
	}
}

void Melee::repair()
{
	sharpness = 100.0;
	if (!isFullyRepaired())
	{
		durability = maxDurability;
		std::cout << name << " repaired successfully!" << std::endl;
	}
	else
	{
		std::cout << name << " is not broken and does not need repair!" << std::endl;
	}
}
