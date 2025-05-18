#pragma once
#include "weapon.h"

class Melee : public Weapon
{
	unsigned durability;
	unsigned maxDurability;
	unsigned sharpness;

public:
	// Konstruktor �s destruktor
	Melee(std::string name, unsigned damage=25, unsigned durability=6);
	~Melee();
	// Weapon virtu�lis met�dusok
	void use() override;
	unsigned getDamage() const override;
	// Saj�t met�dusok
	unsigned getDurability() const;
	unsigned getMaxDurability() const;
	unsigned getSharpness() const;
	bool isBroken() const;
	bool isFullyRepaired() const;
	void repair();
	
};

