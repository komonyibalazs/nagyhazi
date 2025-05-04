#pragma once
#include <iostream>
#include "inventory.h"
#include "upgradeable.h"

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

	virtual void regenerate();
	
	unsigned getHealth() const;
	unsigned getMaxHp() const;
	std::string getName() const;

	void attack(Character& target);
	void heal(int amount);
	bool isAlive() const;
};

