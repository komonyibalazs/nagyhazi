#include "character.h"

Character::Character(std::string name, InventoryManager* inventoryManager)
	: name(name), hp(100), maxHp(100), inventoryManager(inventoryManager)
{}

void Character::heal(int amount)
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
	Weapon* weapon = inventoryManager->getSelectedWeapon();
	if (!weapon) {
		std::cout << name << " has no weapon selected to attack!" << std::endl;
		return;
	}

	unsigned damage = weapon->getDamage();
	target.heal(-static_cast<int>(damage));
}
