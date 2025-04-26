#pragma once
#include "weapon.h"
#include "repairable.h"

class Melee : public Weapon, public Repairable
{
public:
	Melee(std::string name, unsigned damage);
	~Melee();
	void use() override;
	void repair();
	void print() const override;
};

