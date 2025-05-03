#pragma once
#include <vector>
#include <memory>
#include "inventoryManager.h"

class Inventory : public InventoryManager
{
private:
	static const unsigned maxWeaponCount;
	std::vector<std::unique_ptr<Weapon>> weapons;
	unsigned selectedWeaponIndex;

public:
	Inventory();
	~Inventory() override = default;

	void selectNextWeapon();
	void selectPreviousWeapon();
	void takeWeapon(Weapon* weapon);
	void dropSelected();

	void repairSelected() override;
	Weapon* getSelectedWeapon() const override;
	unsigned getSelectedIndex() const override;

	unsigned getMaxWeaponCount() const;

};

