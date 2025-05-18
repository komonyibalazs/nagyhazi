#pragma once
#include "weapon.h"

class Magic : public Weapon
{
	unsigned manaCost;

public:
	// Konstruktor �s destruktor
	Magic(std::string name, unsigned damage=20, unsigned manaCost=20);
	~Magic();
	// Weapon virtu�lis met�dusok
	unsigned getManaCost() const;
	void use() override;
};