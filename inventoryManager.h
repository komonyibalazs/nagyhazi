#pragma once
#include "weapon.h"

class InventoryManager
{
public:
	virtual ~InventoryManager() = default;
	virtual Weapon* getSelectedWeapon() const = 0;
	virtual unsigned getSelectedIndex() const = 0;
	virtual void repairSelected() = 0;
};

