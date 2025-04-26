#pragma once
#include "weapon.h"
#include <vector>
#include <memory>
#include "upgradeable.h"

class Character
{
	static unsigned maxWeaponCount;

protected:
	std::string name;
	unsigned hp;
	unsigned maxHp;

	std::vector<std::unique_ptr<Weapon>> weapons;
	unsigned selectedWeaponIndex;

public:
	Character(std::string name);
	virtual ~Character() = default;

	void heal(int amount);
	
	unsigned getHealth() const;
	
	void selectNextWeapon();
	void selectPreviousWeapon();
	void takeWeapon(Weapon* weapon);
	void dropSelected();
	bool isAlive() const;

	virtual void regenerate() = 0;
	virtual void attack(Character& target) = 0;
	virtual void repairSelected() = 0;
};

