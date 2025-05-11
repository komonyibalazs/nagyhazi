#pragma once
#include "weapon.h"

class Melee : public Weapon
{
	double sharpness;
	unsigned durability;
	unsigned maxDurability;

public:
	Melee(std::string name, unsigned damage=20, unsigned durability=6);
	~Melee();
	unsigned getSharpness() const;
	
	unsigned getDamage() const override;
	void use() override;
	
	unsigned getDurability() const;
	unsigned getMaxDurability() const;
	bool isBroken() const;
	bool isFullyRepaired() const;
	void repair();
	
};

