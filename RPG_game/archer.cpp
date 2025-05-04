#include "archer.h"

Archer::Archer(const std::string& name, const bool& isPlayer) : Character(name, isPlayer) 
{
	inventory.takeWeapon(new Ranged("Bow", 20, 3));
}

Archer::~Archer()
{
	inventory.clearWeapons();
}

void Archer::regenerate()
{
	Character::regenerate();
	Ranged* weapon = (Ranged*)(inventory.getSelectedWeapon());
	weapon->reload();
}
