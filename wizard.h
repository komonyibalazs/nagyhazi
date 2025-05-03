#pragma once
#include "character.h"
class Wizard : public Character, public Upgradeable
{
	unsigned mana;
	unsigned maxMana;

public:
	Wizard(std::string name);
	~Wizard();
	unsigned getMana() const;
	void levelUp();
	void regenerate();
};

