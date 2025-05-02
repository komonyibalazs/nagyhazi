#include "character.h"

const unsigned Character::maxWeaponCount = 2;

Character::Character(std::string name) : name(name), hp(100), maxHp(100), selectedWeaponIndex(0)
{
	weapons.reserve(maxWeaponCount);
}

void Character::heal(int amount)
{
}

unsigned Character::getHealth() const
{
	return 0;
}

void Character::selectNextWeapon()
{
}

void Character::selectPreviousWeapon()
{
}

void Character::takeWeapon(Weapon* weapon)
{
}

void Character::dropSelected()
{
}

bool Character::isAlive() const
{
	return false;
}
