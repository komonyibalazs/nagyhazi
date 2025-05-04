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
	const bool isPlayer;
	Inventory inventory;


public:
	Character(std::string name, const bool isPlayer);
	virtual ~Character() = default;

	virtual void regenerate();
	
	bool isPlayerCharacter() const;
	unsigned getHealth() const;
	unsigned getMaxHp() const;
	std::string getName() const;
	Inventory& getInventory();

	void attack(Character& target);
	void changeHealth(int amount);
	bool isAlive() const;
};

