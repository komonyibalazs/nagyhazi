#include "melee.h"

using namespace std;

Melee::Melee(string name, unsigned damage, unsigned durability)
	: Weapon(name, damage), durability(durability), maxDurability(durability), sharpness(100)
{
}

Melee::~Melee()
{
}

void Melee::use()
{
	if (isBroken()) {
		cout << "Weapon is broken!" << endl;
		return;
	}
	cout << "Using " << getName() << " with damage: " << getDamage() << endl;
	sharpness = (sharpness > 0) ? sharpness - 10 : 0;
	durability--;
}

unsigned Melee::getDamage() const
{
	return damage * sharpness / 100;
}

unsigned Melee::getDurability() const
{
	return durability;
}

unsigned Melee::getMaxDurability() const
{
	return maxDurability;
}

unsigned Melee::getSharpness() const
{
	return sharpness;
}

bool Melee::isBroken() const
{
	return durability == 0;
}

bool Melee::isFullyRepaired() const
{
	return durability == maxDurability && sharpness == 100;
}

void Melee::repair()
{
	if (!isFullyRepaired()) {
		durability = maxDurability;
		sharpness = 100;
		cout << "Weapon repaired!" << endl;
	}
	else {
		cout << "Weapon is already fully repaired!" << endl;
	}
}