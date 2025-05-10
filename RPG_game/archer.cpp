#include "archer.h"

Archer::Archer(const std::string& name) : Character(name)
{
	takeWeapon(new Ranged("Bow", 20, 4));
}

Archer::~Archer()
{
	clearWeapons();
}

void Archer::regenerate()
{
	Character::regenerate();
	Ranged* weapon = (Ranged*)(getSelectedWeapon());
	if(weapon) weapon->reload();
}
