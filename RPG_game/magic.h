#pragma once
#include "weapon.h"

class Magic : public Weapon
{
	unsigned manaCost;

public:
	// Konstruktor és destruktor
	Magic(std::string name, unsigned damage=20, unsigned manaCost=20);
	~Magic();
	// Weapon virtuális metódusok
	unsigned getManaCost() const;
	void use() override;
};