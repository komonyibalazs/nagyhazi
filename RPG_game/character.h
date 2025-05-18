#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "weapon.h"

class Character
{
protected:
	// név és életerõ 
	std::string name;
	unsigned hp;
	unsigned maxHp;
	// Szint és tapasztalat
	unsigned level;
	unsigned xp;
	unsigned maxXp;
	// fegyverek
	static const unsigned maxWeaponCount;
	std::vector<std::unique_ptr<Weapon>> weapons;
	unsigned selectedWeaponIndex;
	// menekülés és jutalmazás
	bool gotReward = false;
	bool isFleeing = false;
public:
	// Konstruktorok
	Character(std::string name);
	Character(std::string name, unsigned level);
	// Destruktor
	virtual ~Character() = default;
	// virtuális metódusok
	virtual void regenerate();
	virtual void attack(Character& target);
	virtual void levelUp();
	virtual void wonTheBattle(const Character&);
	virtual void changeHealth(int amount);
	// HP és név getterei
	unsigned getHealth() const;
	unsigned getMaxHp() const;
	std::string getName() const;
	// Elérhetõség kezelése
	bool isAlive() const;
	// Szint és tapasztalat kezelése
	unsigned getLevel() const;
	unsigned getExperience() const;
	unsigned getMaxExperience() const;
	void gainXp(unsigned gained);
	// Szintlépés, jutalmazás kezelése 
	bool checkLevelUp() const;
	void setReward(bool gotReward);
	bool wasRewarded() const;
	// Menekülés kezelése
	void setFleeing(bool isFleeing);
	bool getFleeing() const;
	// Weapon kezelés
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

