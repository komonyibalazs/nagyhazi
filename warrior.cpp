#include "warrior.h"

Warrior::Warrior(std::string name) : Character(name), Upgradeable(), shield(100), maxShield(100)
{
}

Warrior::~Warrior()
{
}

unsigned Warrior::getShield() const
{
    return shield;
}

void Warrior::levelUp()
{
    level++;
	xp = xp-maxXp;
	maxXp += 100;
	maxHp += 10;
	shield += 10;
}

void Warrior::regenerate()
{
	if (hp < maxHp)
	{
		hp += (double)hp/(double)maxHp*0.25;
	}
	if (shield < maxShield)
	{
		shield += (double)shield/(double)maxShield*0.25;
	}
}

void Warrior::attack(Character& target)
{
	if (target.isAlive() && isAlive())
	{
		if (selectedWeaponIndex < weapons.size())
		{
			weapons[selectedWeaponIndex]->use();
		}
		else
		{
			std::cout << "No weapon selected!" << std::endl;
		}
	}
	else
	{
		std::cout << "Enemy is already dead!" << std::endl;
	}
}

void Warrior::repairSelected()
{
}
