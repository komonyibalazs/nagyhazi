#pragma once
#include "character.h"
#include "melee.h"

class Warrior : public Character
{
	unsigned shield;
	unsigned maxShield;

public:
	Warrior(std::string name);
	~Warrior();
	int getShield() const;
	void levelUp();
	void regenerate();
	void changeHealth(int amount);
};

