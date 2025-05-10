#pragma once
#include "character.h"
#include "ranged.h"
class Archer : public Character
{
public:
	Archer(const std::string& name);
	~Archer() override;
	void regenerate() override;
};

