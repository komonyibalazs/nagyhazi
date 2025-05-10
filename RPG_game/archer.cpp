#include "archer.h"

using namespace std;

Archer::Archer(const string& name) : Character(name)
{
	takeWeapon(new Ranged("Bow"));
}

Archer::Archer(const string& name, unsigned level) : Character(name, level)
{
    takeWeapon(new Ranged("Bow", 20+(level-1)*10, 4+level-1));
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

void Archer::levelUp()
{
	if (xp >= maxXp)
	{
		maxHp = 100 + (level - 1) * 50;
		hp = maxHp;
	}
	Character::levelUp();
}
