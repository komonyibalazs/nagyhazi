#pragma once
#include "weapon.h"

class Magic : public Weapon
{
	unsigned manaCost;

public:
	Magic(std::string name, unsigned damage=20, unsigned manaCost=20);
	~Magic();
	unsigned getManaCost() const;
	void use() override;
};