#include "melee.h"

Melee::Melee(std::string name, unsigned damage, unsigned durability) : Weapon(name, damage), Repairable(durability), sharpness(100)
{}

Melee::~Melee()
{
}

void Melee::use()
{
	if (!isBroken()) 
	{
		durability--;
		damage *= sharpness/100;
		sharpness -= 5;
		std::cout << name << " used successfully!" << std::endl;
		std::cout << damage << " damage dealt with: " << name << std::endl;
	}
	else 
	{
		std::cout << name << " is broken and cannot be used!" << std::endl;
	}
}

void Melee::repair()
{
	sharpness = 100;
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
