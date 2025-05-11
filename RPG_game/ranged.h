#pragma once
#include "weapon.h"

class Ranged : public Weapon
{
	unsigned ammo;
	unsigned maxAmmo;

public:
	Ranged(std::string name, unsigned damage=20, unsigned maxAmmo=4);
	~Ranged() override = default;
	void use() override;

	unsigned getAmmo() const ;
	unsigned getMaxAmmo() const;
	bool isOutOfAmmo() const;
	void reload();
};

