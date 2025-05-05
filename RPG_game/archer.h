#pragma once
#include "character.h"
#include "ranged.h"
class Archer : public Character, public Upgradeable
{
public:
	Archer(const std::string& name, const bool isPlayer);
	~Archer() override;
	void regenerate() override;
};

