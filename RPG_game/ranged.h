#pragma once
#include "weapon.h"
class Ranged : public Weapon
{
	unsigned ammo;
	unsigned maxAmmo;

public:
	Ranged(std::string name,unsigned damage, unsigned maxAmmo);
	~Ranged() override = default;
	void use() override;
	unsigned getAmmo() const;
	unsigned getMaxAmmo() const;
	void reload();
};

