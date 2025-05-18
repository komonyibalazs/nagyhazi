#include "weapon.h"

using namespace std;

Weapon::Weapon(string name, int damage) : name(name), damage(damage)
{
	try {
		if (damage < 0) {
			throw invalid_argument("Weapon damage cannot be negative!");
		}
		if (name.empty()) {
			throw invalid_argument("Weapon name cannot be empty!");
		}
	}
	catch (const invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		this->name = "Unknown";
		this->damage = 0;
	}
	catch (const exception& e) {
		cerr << "Exception in Weapon constructor: " << e.what() << endl;
		this->name = "Unknown";
		this->damage = 0;
	}
}

string Weapon::getName() const
{
	return name;
}

unsigned Weapon::getDamage() const
{
	return damage;
}

