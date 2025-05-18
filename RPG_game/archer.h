#pragma once
#include "character.h"
#include "ranged.h"

class Archer : public Character
{
public:
	// Konstruktorok
	Archer(const std::string& name);
	Archer(const std::string& name, unsigned level);
	// Destruktor
	~Archer() override;
	// Character virtu�lis met�dusok
	void regenerate() override;
	void levelUp() override;
};

