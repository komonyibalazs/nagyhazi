#include "wizard.h"

Wizard::Wizard(std::string name) : Character(name), Upgradeable(), mana(100), maxMana(100)
{
}
Wizard::~Wizard()
{
}

unsigned Wizard::getMana() const
{
	return 0;
}

void Wizard::levelUp()
{
}

void Wizard::regenerate()
{
}

void Wizard::attack(Character& target)
{
}

void Wizard::repairSelected()
{
}
