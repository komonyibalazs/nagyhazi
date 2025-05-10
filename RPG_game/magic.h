#pragma once
#include "weapon.h"
#include "mana_consuming.h"

class Magic : public Weapon, public ManaConsuming
{
	unsigned manaCost;

public:
	Magic(std::string name, unsigned damage=20, unsigned manaCost=20);
	~Magic();
	unsigned getManaCost() const override;
	void use() override;
};