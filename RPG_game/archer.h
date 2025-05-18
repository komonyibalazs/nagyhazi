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
	// Character virtuális metódusok
	void regenerate() override;
	void levelUp() override;
};

