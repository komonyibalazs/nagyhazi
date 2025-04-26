#pragma once
#include "weapon.h"

class Magic : public Weapon
{
	unsigned manaCost;

public:
	Magic(std::string name, unsigned damage, unsigned manaCost);
	~Magic() override = default;
	unsigned getManaCost() const;
	void setManaCost(unsigned manaCost);
	void use() override;
};