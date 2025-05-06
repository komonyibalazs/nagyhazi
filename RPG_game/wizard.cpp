#include "wizard.h"

Wizard::Wizard(std::string name, const bool isPlayer) : Character(name, isPlayer), Upgradeable(), mana(100), maxMana(100)
{
	inventory.takeWeapon(new Magic("Wand", 35, 20));
}
Wizard::~Wizard()
{
	inventory.clearWeapons();
}

unsigned Wizard::getMana() const
{
	return mana;
}

void Wizard::changeMana(int amount)
{
	int mana = this->mana;
	mana += amount;
	if (mana >= maxMana)
		this->mana = maxMana;
	else if (mana <= 0)
		this->mana = 0;
	else
		this->mana = mana;
}

void Wizard::levelUp()
{
	if (xp >= maxXp)
	{
		hp *= 1.2;
		maxMana *= 1.1;
		mana = maxMana;
	}
Upgradeable::levelUp();
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

void Wizard::attack(Character& target)
{
	Magic* magicWeapon = (Magic*)inventory.getSelectedWeapon();
	changeMana(-(int)magicWeapon->getManaCost());
	Character::attack(target);
}

