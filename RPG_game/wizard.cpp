#include "wizard.h"

using namespace std;

Wizard::Wizard(string name) : Character(name), mana(100), maxMana(100)
{
	try 
	{
		takeWeapon(new Magic("Wand"));
	}
	catch (const bad_alloc& e)
	{
		cerr << "Wizard constructor: Memory allocation failed for weapon " << endl;
		cerr << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Exception in Wizard constructor: " << e.what() << endl;
	}
}

Wizard::Wizard(string name, unsigned level) : Character(name, level)
{
	try
	{
		this->maxMana = 100 + (level - 1) * 50;
		this->mana = maxMana;
		takeWeapon(new Magic("Wand", 20 + (level - 1) * 10, 20 + (level - 1) * 10));
	}
	catch (const bad_alloc& e)
	{
		cerr << "Wizard constructor 2: Memory allocation failed for weapon " << endl;
		cerr << e.what() << endl;
	}
	catch (const exception& e)
	{
		cerr << "Exception in Wizard constructor 2: " << e.what() << endl;
	}
}

Wizard::~Wizard()
{
	clearWeapons();
}

unsigned Wizard::getMana() const
{
	return mana;
}

unsigned Wizard::getMaxMana() const
{
	return maxMana;
}

void Wizard::changeMana(int amount)
{
	int mana = this->mana;
	mana += amount;
	if (mana >= (int)maxMana)
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
		maxMana = 100 + level * 50;
		mana = maxMana;
	}
	Character::levelUp();
}

void Wizard::regenerate()
{
	Character::regenerate();
	if (mana < maxMana && mana+maxMana*0.5 < maxMana)
	{
		mana += static_cast<unsigned>(maxMana * 0.5);
	}
	else
	{
		mana = maxMana;
	}
}

void Wizard::attack(Character& target)
{
	Magic* magicWeapon = (Magic*)getSelectedWeapon();
	if(magicWeapon) changeMana(-(int)magicWeapon->getManaCost());
	Character::attack(target);
}

void Wizard::wonTheBattle(const Character& enemy)
{
	mana = maxMana;
	Character::wonTheBattle(enemy);
}

