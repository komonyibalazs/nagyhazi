#pragma once
#include "character.h"
#include "ranged.h"
class Archer : public Character
{
public:
	Archer(const std::string& name);
	Archer(const std::string& name, unsigned level);
	~Archer() override;
	void regenerate() override;
	void levelUp() override;
};

