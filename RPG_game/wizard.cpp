#include "wizard.h"

Wizard::Wizard(std::string name) : Character(name), Upgradeable(), mana(100), maxMana(100)
{
}
Wizard::~Wizard()
{
}

unsigned Wizard::getMana() const
{
	return mana;
}

void Wizard::levelUp()
{
	Upgradeable::levelUp();
	hp *= 1.2; 
	maxMana *= 1.1;
	mana = maxMana;
}

void Wizard::regenerate()
{
	Character::regenerate();
	if (mana < maxMana && mana+maxMana*0.25 < maxMana)
	{
		mana += maxMana*0.25;
	}
	else
	{
		mana = maxMana;
	}
}

