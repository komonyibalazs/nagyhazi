#include "weapon.h"

Weapon::Weapon(std::string name, unsigned damage) : name(name), damage(damage)
{}

std::string Weapon::getName() const
{
	return name;
}

unsigned Weapon::getDamage() const
{
	return damage;
}

