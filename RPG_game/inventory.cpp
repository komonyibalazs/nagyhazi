#include "inventory.h"

const unsigned Inventory::maxWeaponCount = 2;

Inventory::Inventory() : selectedWeaponIndex(0)
{
	weapons.reserve(maxWeaponCount);
}

Inventory::~Inventory()
{
}

void Inventory::selectNextWeapon()
{

}

void Inventory::selectPreviousWeapon()
{

}

void Inventory::takeWeapon(Weapon* weapon)
{

}

void Inventory::dropSelected()
{

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
