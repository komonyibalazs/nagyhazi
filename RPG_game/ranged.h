#pragma once
#include "weapon.h"

class Ranged : public Weapon
{
	unsigned ammo;
	unsigned maxAmmo;

public:
	// Konstruktor és destruktor
	Ranged(std::string name, unsigned damage=20, unsigned maxAmmo=4);
	~Ranged() override = default;
	// Weapon virtuális metódusok
	void use() override;
	// Saját metódusok
	unsigned getAmmo() const ;
	unsigned getMaxAmmo() const;
	bool isOutOfAmmo() const;
	void reload();
};

