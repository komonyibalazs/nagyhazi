#pragma once
#include "weapon.h"

class Ranged : public Weapon
{
	unsigned ammo;
	unsigned maxAmmo;

public:
	// Konstruktor �s destruktor
	Ranged(std::string name, unsigned damage=20, unsigned maxAmmo=4);
	~Ranged() override = default;
	// Weapon virtu�lis met�dusok
	void use() override;
	// Saj�t met�dusok
	unsigned getAmmo() const ;
	unsigned getMaxAmmo() const;
	bool isOutOfAmmo() const;
	void reload();
};

