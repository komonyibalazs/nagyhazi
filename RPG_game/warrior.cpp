#include "warrior.h"

using namespace std;

Warrior::Warrior(string name) : Character(name), shield(100), maxShield(100)
{
	takeWeapon(new Melee("Sword"));
}

Warrior::Warrior(string name, unsigned level) : Character(name, level), shield(100), maxShield(100)
{
	this->maxShield = 100 + (level - 1) * 50;
	this->shield = maxShield;
	takeWeapon(new Melee("Sword", 25 + (level - 1) * 10, 6 + level - 1));
}

Warrior::~Warrior()
{
	clearWeapons();
}

unsigned Warrior::getShield() const
{
	return shield;
}

unsigned Warrior::getMaxShield() const
{
	return maxShield;
}

void Warrior::setShield(unsigned shield)
{
	this->shield = shield;
}

void Warrior::levelUp()
{
	if (xp >= maxXp)
	{
		maxShield = 100 + level * 50;
		shield = maxShield;
	}
	Character::levelUp();
}

void Warrior::regenerate()
{
	Character::regenerate();
	if (shield < maxShield && shield + maxShield * 0.5 <= maxShield)
	{
		shield += static_cast<unsigned>(maxShield * 0.5);
	}
	else
	{
		shield = maxShield;
	}
}

void Warrior::changeHealth(int amount)
{
	int fullHp = hp + shield + amount;
	if (fullHp < (int)maxHp)
	{
		hp = fullHp;
		shield = 0;
	}
	else if (fullHp >= (int)maxHp)
	{
		hp = maxHp;
		shield = fullHp - maxHp;
	}
	if (fullHp < 0)
	{
		hp = 0;
	}
}

void Warrior::wonTheBattle(const Character& enemy)
{
	shield = maxShield;
	Character::wonTheBattle(enemy);
}