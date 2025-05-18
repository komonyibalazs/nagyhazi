#pragma once
#include "character.h"
#include "magic.h"

class Wizard : public Character
{
	unsigned mana;
	unsigned maxMana;

public:
	// Konstruktorok
	Wizard(std::string name);
	Wizard(std::string name, unsigned level);
	// Destruktor
	~Wizard();
	// Getterek
	unsigned getMana() const;
	unsigned getMaxMana() const;
	// Mana kezel�s
	void changeMana(int amount);
	// Character virtu�lis met�dusok
	void regenerate() override;
	void attack(Character& target) override;
	void levelUp() override;
	void wonTheBattle(const Character&) override;
};

