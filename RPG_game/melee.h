#pragma once
#include "weapon.h"

class Melee : public Weapon
{
	unsigned durability;
	unsigned maxDurability;
	unsigned sharpness;

public:
	Melee(std::string name, unsigned damage=25, unsigned durability=6);
	~Melee();
	
	void use() override;
	unsigned getDamage() const override;

	unsigned getDurability() const;
	unsigned getMaxDurability() const;
	unsigned getSharpness() const;
	bool isBroken() const;
	bool isFullyRepaired() const;
	void repair();
	
};

