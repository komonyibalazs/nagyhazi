#pragma once
#include "character.h"
#include "melee.h"

class Warrior : public Character
{
	unsigned shield;
	unsigned maxShield;

public:
	// Konstruktorok
	Warrior(std::string name);
	Warrior(std::string name, unsigned level);
	// Destruktor
	~Warrior();
	// getterek
	unsigned getShield() const;
	unsigned getMaxShield() const;
	// setter
	void setShield(unsigned shield);
	// Character virtuális metódusok
	void regenerate() override;
	void levelUp() override;
	void wonTheBattle(const Character&) override;
	void changeHealth(int amount) override;
};

