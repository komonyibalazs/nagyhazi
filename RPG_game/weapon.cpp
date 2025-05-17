#include "weapon.h"

Weapon::Weapon(std::string name, int damage) : name(name), damage(damage)
{
	try {
		if (damage < 0) {
			throw std::invalid_argument("Weapon damage cannot be negative!");
		}
		if (name.empty()) {
			throw std::invalid_argument("Weapon name cannot be empty!");
		}
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		this->name = "Unknown";
		this->damage = 0;
	}
}

std::string Weapon::getName() const
{
	return name;
}

unsigned Weapon::getDamage() const
{
	return damage;
}

