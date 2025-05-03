#include "character.h"

Character::Character(std::string name) : name(name), hp(100), maxHp(100)
{
	inventory = Inventory();
}

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
    if (inventory.getSelectedWeaponIndex() >= inventory) {
        std::cout << name << " has no weapon selected to attack!" << std::endl;
        return;
    }
    Weapon* weapon = weapons[selectedWeaponIndex].get();
    unsigned damage = weapon->getDamage();
    Warrior* warriorTarget = dynamic_cast<Warrior*>(&target);
    if (warriorTarget != nullptr)
    {
        if (warriorTarget->getShield() >= damage)
        {
            warriorTarget->heal(-damage);
            damage = 0;
        }
        else
        {
            damage -= warriorTarget->getShield();
            warriorTarget->shield = 0;
        }
    }
    target.heal(-damage);
}
