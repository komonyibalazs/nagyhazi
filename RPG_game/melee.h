#pragma once
#include "weapon.h"
#include "repairable.h"

class Melee : public Weapon, public Repairable
{
	double sharpness;

public:
	Melee(std::string name, unsigned damage, unsigned durability);
	~Melee();
	unsigned getDamage() const override;
	void use() override;
	void repair();
};

