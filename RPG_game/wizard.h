#pragma once
#include "character.h"
#include "magic.h"

class Wizard : public Character
{
	unsigned mana;
	unsigned maxMana;

public:
	Wizard(std::string name);
	~Wizard();
	unsigned getMana() const;
	void changeMana(int amount);
	void levelUp();
	void regenerate();
	void attack(Character& target);
};

