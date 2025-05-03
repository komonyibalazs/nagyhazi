#pragma once
#include "inventory.h"
#include "upgradeable.h"
class Character
{
	

protected:
	std::string name;
	unsigned hp;
	unsigned maxHp;
	InventoryManager* inventoryManager;

public:
	Character(std::string name, InventoryManager* inventoryManager);
	virtual ~Character() = default;

	virtual void regenerate();
	
	unsigned getHealth() const;
	unsigned getMaxHp() const;
	std::string getName() const;

	void attack(Character& target);
	void heal(int amount);
	bool isAlive() const;


};

