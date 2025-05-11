#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "weapon.h"
#include "melee.h"
#include "magic.h"
#include "ranged.h"
#include "repairable.h"

class Character
{
protected:
	std::string name;
	unsigned hp;
	unsigned maxHp;

	unsigned level;
	unsigned xp;
	unsigned maxXp;

	static const unsigned maxWeaponCount;
	std::vector<std::unique_ptr<Weapon>> weapons;
	unsigned selectedWeaponIndex;

	bool gotReward = false;
	bool isFleeing = false;
public:
	Character(std::string name);
	Character(std::string name, unsigned level);
	virtual ~Character() = default;

	virtual void regenerate();
	virtual void attack(Character& target);

	unsigned getHealth() const;
	unsigned getMaxHp() const;
	std::string getName() const;
	
	void changeHealth(int amount);
	bool isAlive() const;

	unsigned getLevel() const;
	unsigned getExperience() const;
	unsigned getMaxExperience() const;
	void gainXp(unsigned gained);
	
	virtual void levelUp();
	virtual void wonTheBattle();
	void setReward(bool gotReward);
	bool wasRewarded() const;
	void setFleeing(bool isFleeing);
	bool getFleeing() const;

	void selectWeapon(unsigned index);
	void takeWeapon(Weapon* weapon);
	void dropSelected();
	void repairSelected();
	void clearWeapons();

	const std::vector<std::unique_ptr<Weapon>>& getWeapons() const;
	Weapon* getSelectedWeapon() const;
	unsigned getSelectedIndex() const;
	unsigned getMaxWeaponCount() const;

	void replaceWeapon(int index, Weapon* newWeapon);
	void displayWeapons() const;
	bool checkLevelUp() const;
};

