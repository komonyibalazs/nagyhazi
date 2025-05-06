#pragma once
#include "character.h"
#include "magic.h"

class Wizard : public Character, public Upgradeable
{
	unsigned mana;
	unsigned maxMana;

public:
	Wizard(std::string name, const bool isPlayer = false);
	~Wizard();
	unsigned getMana() const;
	void changeMana(int amount);
	void levelUp();
	void regenerate();
	void attack(Character& target);
};

