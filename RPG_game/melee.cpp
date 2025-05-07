#include "melee.h"

Melee::Melee(std::string name, unsigned damage, unsigned durability)
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
		std::cout << name << " used successfully!" << std::endl;
		std::cout << trueDamage << " damage dealt with: " << name << std::endl;
	}
	else 
	{
		std::cout << name << " is broken and cannot be used!" << std::endl;
	}
}

unsigned Melee::getDurability() const
{
	return durability;
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
		std::cout << name << " repaired successfully!" << std::endl;
	}
	else
	{
		std::cout << name << " is not broken and does not need repair!" << std::endl;
	}
}
