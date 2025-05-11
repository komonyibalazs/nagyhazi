#pragma once
#include "character.h"
#include "melee.h"

class Warrior : public Character
{
	unsigned shield;
	unsigned maxShield;

public:
	Warrior(std::string name);
	Warrior(std::string name, unsigned level);
	~Warrior();
	unsigned getShield() const;
	unsigned getMaxShield() const;
	void levelUp();
	void regenerate();
	void changeHealth(int amount);
	void wonTheBattle() override;
};

