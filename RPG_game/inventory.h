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
	~Inventory();

	void selectWeapon(unsigned index);
	void takeWeapon(Weapon* weapon);
	void dropSelected();
	void repairSelected();
	void clearWeapons();

	std::vector<std::unique_ptr<Weapon>>& getWeapons();
	Weapon* getSelectedWeapon() const;
	unsigned getSelectedIndex() const;
	unsigned getMaxWeaponCount() const;


};

