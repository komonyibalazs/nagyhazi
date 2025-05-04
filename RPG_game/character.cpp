#include "character.h"

Character::Character(std::string name, const bool isPlayer=false) : hp(100), maxHp(100), name(name), inventory(), isPlayer(isPlayer)
{
}

void Character::changeHealth(int amount)
{
	hp += amount;
	if (hp > maxHp)
	{
		hp = maxHp;
	}
	else if (hp <= 0)
	{
		hp = 0;
	}
}

unsigned Character::getHealth() const
{
	return hp;
}

unsigned Character::getMaxHp() const
{
    return maxHp;
}

std::string Character::getName() const
{
	return name;
}

Inventory& Character::getInventory()
{
	return inventory;
}

bool Character::isAlive() const
{
	return hp > 0;
}


void Character::regenerate()
{
	if (hp < maxHp && hp+maxHp*0.25 <maxHp)
	{
		hp += maxHp*0.25;
	}
	else
	{
		hp = maxHp;
	}
}

void Character::attack(Character& target)
{
	Weapon* weapon = inventory.getSelectedWeapon();
	if (!weapon) {
		std::cout << name << " has no weapon selected to attack!" << std::endl;
		return;
	}
	weapon->use();
	unsigned damage = weapon->getDamage();
	target.changeHealth(-(int)damage);
}
