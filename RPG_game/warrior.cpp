#include "warrior.h"

Warrior::Warrior(std::string name) : Character(name), shield(100), maxShield(100)
{
	takeWeapon(new Melee("Sword", 20, 6));
}

Warrior::~Warrior()
{
	clearWeapons();
}

int Warrior::getShield() const
{
    return shield;
}

void Warrior::levelUp()
{
	if (xp >= maxXp)
	{
		hp *= 1.2;
		maxShield *= 1.2;
		shield = maxShield;
	}
	Character::levelUp();
}

void Warrior::regenerate()
{
	Character::regenerate();
	if (shield < maxShield && shield+maxShield*0.25<=maxShield)
	{
		shield += maxShield*0.25;
	}
    else
	{
		shield = maxShield;
	}
}

void Warrior::changeHealth(int amount)
{
	int fullHp = hp + shield + amount;
	if (fullHp < maxHp)
	{
		hp = fullHp;
		shield = 0;
	}
	else if(fullHp >= maxHp)
	{
		hp = maxHp;
		shield = fullHp - maxHp;
	}
	if (fullHp < 0)
	{
		hp = 0;
	}
}


