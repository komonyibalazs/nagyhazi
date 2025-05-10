#include "magic.h"

using namespace std;

Magic::Magic(string name, unsigned damage, unsigned manaCost) : Weapon(name, damage), manaCost(manaCost)
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
	cout << "Using magic: " << getName() << " with damage: " << getDamage() << " and mana cost: " << getManaCost() << endl;
}
