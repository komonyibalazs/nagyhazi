#pragma once
#include "inventory.h"
#include "upgradeable.h"
#include "warrior.h"
class Character
{
	

protected:
	std::string name;
	unsigned hp;
	unsigned maxHp;
	Inventory inventory;

public:
	Character(std::string name);
	virtual ~Character() = default;

	virtual void heal(int amount);
	virtual void regenerate();
	
	unsigned getHealth() const;
	unsigned getMaxHp() const;
	std::string getName() const;

	void attack(Character& target);
	bool isAlive() const;


};

