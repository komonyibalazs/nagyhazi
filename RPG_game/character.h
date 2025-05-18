#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "weapon.h"

class Character
{
protected:
	// n�v �s �leter� 
	std::string name;
	unsigned hp;
	unsigned maxHp;
	// Szint �s tapasztalat
	unsigned level;
	unsigned xp;
	unsigned maxXp;
	// fegyverek
	static const unsigned maxWeaponCount;
	std::vector<std::unique_ptr<Weapon>> weapons;
	unsigned selectedWeaponIndex;
	// menek�l�s �s jutalmaz�s
	bool gotReward = false;
	bool isFleeing = false;
public:
	// Konstruktorok
	Character(std::string name);
	Character(std::string name, unsigned level);
	// Destruktor
	virtual ~Character() = default;
	// virtu�lis met�dusok
	virtual void regenerate();
	virtual void attack(Character& target);
	virtual void levelUp();
	virtual void wonTheBattle(const Character&);
	virtual void changeHealth(int amount);
	// HP �s n�v getterei
	unsigned getHealth() const;
	unsigned getMaxHp() const;
	std::string getName() const;
	// El�rhet�s�g kezel�se
	bool isAlive() const;
	// Szint �s tapasztalat kezel�se
	unsigned getLevel() const;
	unsigned getExperience() const;
	unsigned getMaxExperience() const;
	void gainXp(unsigned gained);
	// Szintl�p�s, jutalmaz�s kezel�se 
	bool checkLevelUp() const;
	void setReward(bool gotReward);
	bool wasRewarded() const;
	// Menek�l�s kezel�se
	void setFleeing(bool isFleeing);
	bool getFleeing() const;
	// Weapon kezel�s
	void selectWeapon(unsigned index);
	void takeWeapon(Weapon* weapon);
	void replaceWeapon(int index, Weapon* newWeapon);
	void clearWeapons();
	void repairSelected();
	void displayWeapons() const;
	// Weapon getterek
	const std::vector<std::unique_ptr<Weapon>>& getWeapons() const;
	Weapon* getSelectedWeapon() const;
	unsigned getSelectedIndex() const;
	unsigned getMaxWeaponCount() const;

};

