#include "wizard.h"

using namespace std;

Wizard::Wizard(string name) : Character(name), mana(100), maxMana(100)
{
	takeWeapon(new Magic("Wand"));
}

Wizard::Wizard(string name, unsigned level) : Character(name, level)
{
	this->maxMana = 100 + (level - 1) * 50;
	this->mana = maxMana;
	takeWeapon(new Magic("Wand", 20+(level-1)*10, 20+(level-1)*10));
}

Wizard::~Wizard()
{
	clearWeapons();
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
		maxHp = 100 + (level - 1) * 50;
		hp = maxHp;
		maxMana *= 100 + (level-1) * 50;
		mana = maxMana;
	}
Character::levelUp();
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
	Magic* magicWeapon = (Magic*)getSelectedWeapon();
	changeMana(-(int)magicWeapon->getManaCost());
	Character::attack(target);
}

