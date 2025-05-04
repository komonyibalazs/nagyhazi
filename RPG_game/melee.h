#pragma once
#include "weapon.h"
#include "repairable.h"

class Melee : public Weapon, public Repairable
{
	unsigned sharpness;

public:
	Melee(std::string name, unsigned damage, unsigned durability);
	~Melee();
	void use() override;
	void repair();
};

