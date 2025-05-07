#pragma once
#include "weapon.h"
#include "ammo_consuming.h"

class Ranged : public Weapon, public AmmoConsuming
{
	unsigned ammo;
	unsigned maxAmmo;

public:
	Ranged(std::string name, unsigned damage, unsigned maxAmmo);
	~Ranged() override = default;
	void use() override;

	unsigned getAmmo() const override;
	unsigned getMaxAmmo() const override;
	bool isOutOfAmmo() const override;
	void reload() override;
};

