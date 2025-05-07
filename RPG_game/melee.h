#pragma once
#include "weapon.h"
#include "repairable.h"

class Melee : public Weapon, public Repairable
{
	double sharpness;
	unsigned durability;
	unsigned maxDurability;

public:
	Melee(std::string name, unsigned damage, unsigned durability);
	~Melee();
	unsigned getSharpness() const;
	
	unsigned getDamage() const override;
	void use() override;
	
	unsigned getDurability() const override;
	bool isBroken() const override;
	bool isFullyRepaired() const override;
	void repair() override;
	
};

