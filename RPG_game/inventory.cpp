#include "inventory.h"

const unsigned Inventory::maxWeaponCount = 2;

Inventory::Inventory() : selectedWeaponIndex(0)
{
	weapons.reserve(maxWeaponCount);
}

Inventory::~Inventory()
{
}

void Inventory::selectWeapon(unsigned index)
{
	if (index >= weapons.size()) {
		std::cout << "Invalid weapon index!" << std::endl;
		return;
	}
	selectedWeaponIndex = index;
	std::cout << "Selected weapon: " << weapons[selectedWeaponIndex]->getName() << std::endl;
}

void Inventory::takeWeapon(Weapon* weapon)
{
	if (weapons.size() >= maxWeaponCount) {
		std::cout << "Inventory is full! Cannot take more weapons." << std::endl;
		return;
	}
	if (weapon) {
		weapons.push_back(std::unique_ptr<Weapon>(weapon));
		std::cout << "Weapon taken: " << weapon->getName() << std::endl;
	}
	else 
	{
		std::cout << "Invalid weapon!" << std::endl;
	}

}

void Inventory::dropSelected()
{
	if (weapons.empty() || selectedWeaponIndex >= weapons.size()) {
		std::cout << "No weapon selected to drop!" << std::endl;
		return;
	}
	std::cout << "Dropped weapon: " << weapons[selectedWeaponIndex]->getName() << std::endl;
	weapons.erase(weapons.begin() + selectedWeaponIndex);
	selectedWeaponIndex = 0;

}

void Inventory::repairSelected()
{
    if (weapons.empty() || selectedWeaponIndex >= weapons.size()) {
        std::cout << "No weapon selected to repair!" << std::endl;
        return;
    }

    Weapon* weapon = weapons[selectedWeaponIndex].get();

    Repairable* repairableWeapon = dynamic_cast<Repairable*>(weapon);
    if (!repairableWeapon) {
        std::cout << "There is no need to repair this weapon!" << std::endl;
        return;
    }

    if (repairableWeapon->isFullyRepaired()) {
        std::cout << "This weapon is already fully repaired!" << std::endl;
        return;
    }

    repairableWeapon->repair();

    std::cout << weapon->getName() << " got repaired." << std::endl;
}

void Inventory::clearWeapons()
{
	for (auto& weapon : weapons) {
		weapon.reset();
	}
	weapons.clear();
	selectedWeaponIndex = 0;
	std::cout << "All weapons cleared from inventory." << std::endl;
}

std::vector<std::unique_ptr<Weapon>>& Inventory::getWeapons()
{
	return weapons;
}

Weapon* Inventory::getSelectedWeapon() const
{
	if (weapons.empty() || selectedWeaponIndex >= weapons.size()) {
		std::cout << "No weapon selected!" << std::endl;
		return nullptr;
	}
	return weapons[selectedWeaponIndex].get();
}

unsigned Inventory::getSelectedIndex() const
{
    return selectedWeaponIndex;
}

unsigned Inventory::getMaxWeaponCount() const
{
    return maxWeaponCount;
}
