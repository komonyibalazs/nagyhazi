#pragma once
#include "character.h"
#include "melee.h"

class Warrior : public Character, public Upgradeable
{
	unsigned shield;
	unsigned maxShield;

public:
	Warrior(std::string name, const bool& isPlayer);
	~Warrior();
	unsigned getShield() const;
	void levelUp();
	void regenerate();
	void heal(int amount);
};

