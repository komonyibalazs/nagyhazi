#include "character.h"

const unsigned Character::maxWeaponCount = 3;

Character::Character(std::string name) : 
	name(name), hp(100), maxHp(100), level(1), xp(0), maxXp(100), selectedWeaponIndex(0)
{
	weapons.reserve(maxWeaponCount);
}

void Character::changeHealth(int amount)
{
	int hp = this->hp+amount;
	if (hp > (int)maxHp)
	{
		hp = maxHp;
	}
	else if (hp <= 0)
	{
		hp = 0;
	}
	this->hp = hp;
}

unsigned Character::getHealth() const
{
	return hp;
}

unsigned Character::getMaxHp() const
{
    return maxHp;
}

std::string Character::getName() const
{
	return name;
}

bool Character::isAlive() const
{
	return hp > 0;
}

unsigned Character::getLevel() const
{
	return level;
}

unsigned Character::getExperience() const
{
	return xp;
}

unsigned Character::getMaxExperience() const
{
	return maxXp;
}

void Character::gainXp(unsigned gained)
{
	xp += gained;
	if (xp >= maxXp)
	{
		levelUp();
	}
	else if (xp < 0)
	{
		xp = 0;
	}
}

void Character::levelUp()
{
	if (xp >= maxXp)
	{
		level++;
		xp -= maxXp;
		maxXp *= 1.1;
	}
}

void Character::selectWeapon(unsigned index)
{
	if (index >= weapons.size()) {
		std::cout << "Invalid weapon index!" << std::endl;
		return;
	}
	selectedWeaponIndex = index;
	std::cout << "Selected weapon: " << weapons[selectedWeaponIndex]->getName() << std::endl;
}

void Character::takeWeapon(Weapon* weapon)
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

void Character::dropSelected()
{
	if (weapons.empty() || selectedWeaponIndex >= weapons.size()) {
		std::cout << "No weapon selected to drop!" << std::endl;
		return;
	}
	std::cout << "Dropped weapon: " << weapons[selectedWeaponIndex]->getName() << std::endl;
	weapons.erase(weapons.begin() + selectedWeaponIndex);
	selectedWeaponIndex = 0;
}

void Character::repairSelected()
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

void Character::clearWeapons()
{
	for (auto& weapon : weapons) {
		weapon.reset();
	}
	weapons.clear();
	selectedWeaponIndex = 0;
	std::cout << "All weapons cleared from inventory." << std::endl;
}

const std::vector<std::unique_ptr<Weapon>>& Character::getWeapons() const
{
	return weapons;
}

Weapon* Character::getSelectedWeapon() const
{
	if (weapons.empty()) {
		std::cout << "No weapon selected!" << std::endl;
		return nullptr;
	}
	return weapons[selectedWeaponIndex].get();
}

unsigned Character::getSelectedIndex() const
{
	return selectedWeaponIndex;
}

unsigned Character::getMaxWeaponCount() const
{
	return maxWeaponCount;
}


void Character::regenerate()
{
	if (hp < maxHp && hp+maxHp*0.25 <maxHp)
	{
		hp += maxHp*0.25;
	}
	else
	{
		hp = maxHp;
	}
}

void Character::attack(Character& target)
{
	Weapon* weapon = getSelectedWeapon();
	if (!weapon) {
		std::cout << name << " has no weapon selected to attack!" << std::endl;
		return;
	}
	if (!target.isAlive()) {
		std::cout << target.getName() << " is already dead!" << std::endl;
		return;
	}
	unsigned damage = weapon->getDamage();
	target.changeHealth(-(int)damage);
	weapon->use();
}
