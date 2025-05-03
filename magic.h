#pragma once
#include "weapon.h"

class Magic : public Weapon
{
	unsigned manaCost;

public:
	Magic(std::string name, unsigned damage, unsigned manaCost);
	~Magic();
	unsigned getManaCost() const;
	void use() override;
};