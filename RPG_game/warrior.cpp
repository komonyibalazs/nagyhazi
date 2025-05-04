#include "warrior.h"

Warrior::Warrior(std::string name, const bool& isPlayer) : Character(name, isPlayer), Upgradeable(), shield(100), maxShield(100)
{
	inventory.takeWeapon(new Melee("Sword", 20, 5));
}

Warrior::~Warrior()
{
	inventory.clearWeapons();
}

unsigned Warrior::getShield() const
{
    return shield;
}

void Warrior::levelUp()
{
	Upgradeable::levelUp();
    hp *= 1.2;
    maxShield *= 1.2;
	shield = maxShield;
}

void Warrior::regenerate()
{
	Character::regenerate();
	if (shield < maxShield && shield+maxShield*0.25)
	{
		shield += maxShield*0.25;
	}
    else
	{
		shield = maxShield;
	}
}

void Warrior::heal(int amount)
{
	if (amount >= 0)
	{
		hp += amount;
		if (hp > maxHp)
		{
			shield += hp-maxHp;
		}
	}
	else
	{
		shield += amount;
		if (shield < 0)
		{
			hp += shield;
		}
	}
	if (hp > maxHp)
	{
		hp = maxHp;
	}
	else if (hp < 0)
	{
		hp = 0;
	}
	if (shield > maxShield)
	{
		shield = maxShield;
	}
	else if (shield < 0)
	{
		shield = 0;
	}
}


