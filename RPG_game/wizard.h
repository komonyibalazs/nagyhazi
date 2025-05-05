#pragma once
#include "character.h"
#include "magic.h"

class Wizard : public Character, public Upgradeable
{
	unsigned mana;
	unsigned maxMana;

public:
	Wizard(std::string name, const bool isPlayer);
	~Wizard();
	unsigned getMana() const;
	void levelUp();
	void regenerate();
};

