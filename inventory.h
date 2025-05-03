#pragma once
#include <vector>
#include <memory>
#include "weapon.h"
#include "repairable.h"

class Inventory
{
private:
	static const unsigned maxWeaponCount;
	std::vector<std::unique_ptr<Weapon>> weapons;
	unsigned selectedWeaponIndex;

public:
	Inventory();
	virtual ~Inventory() = default;
	void selectNextWeapon();
	void selectPreviousWeapon();
	void takeWeapon(Weapon* weapon);
	void dropSelected();
	void repairSelected();
	Weapon* getSelectedWeapon() const;
	unsigned getSelectedWeaponIndex() const;
	unsigned getMaxWeaponCount() const;

};

