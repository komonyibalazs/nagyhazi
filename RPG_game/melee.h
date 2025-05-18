#pragma once
#include "weapon.h"

class Melee : public Weapon
{
	unsigned durability;
	unsigned maxDurability;
	unsigned sharpness;

public:
	// Konstruktor és destruktor
	Melee(std::string name, unsigned damage=25, unsigned durability=6);
	~Melee();
	// Weapon virtuális metódusok
	void use() override;
	unsigned getDamage() const override;
	// Saját metódusok
	unsigned getDurability() const;
	unsigned getMaxDurability() const;
	unsigned getSharpness() const;
	bool isBroken() const;
	bool isFullyRepaired() const;
	void repair();
	
};

