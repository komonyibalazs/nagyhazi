#include "magic.h"

Magic::Magic(std::string name, unsigned damage, unsigned manaCost) : Weapon(name, damage), manaCost(manaCost)
{}

Magic::~Magic()
{
}

unsigned Magic::getManaCost() const
{
	return manaCost;
}

void Magic::use()
{
	std::cout << "Using magic: " << getName() << " with damage: " << getDamage() << " and mana cost: " << getManaCost() << std::endl;
}
