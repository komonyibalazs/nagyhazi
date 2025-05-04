#include "magic.h"

Magic::Magic(std::string name, unsigned damage, unsigned manaCost)
{
}

Magic::~Magic()
{
}

unsigned Magic::getManaCost() const
{
	return manaCost;
}

void Magic::use()
{
	std::cout << "Casting " << name << " for " << damage << " damage!" << std::endl;
	std::cout << "Mana cost: " << manaCost << std::endl;
}
