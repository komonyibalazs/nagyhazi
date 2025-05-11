#include "character.h"

using namespace std;

const unsigned Character::maxWeaponCount = 3;

Character::Character(string name) : 
	name(name), hp(100), maxHp(100), level(1), xp(0), maxXp(100), selectedWeaponIndex(0)
{
	weapons.reserve(maxWeaponCount);
}

Character::Character(string name, unsigned level) :
	name(name), level(level), xp(0), selectedWeaponIndex(0)
{
	this->maxHp = 100 + (level-1) * 50;
	this->hp = maxHp;
	this->maxXp = 100 + (level-1) * 20;
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

void Character::wonTheBattle()
{
	hp = maxHp;
	Ranged* rangedWeapon = dynamic_cast<Ranged*>(getSelectedWeapon());
	if (rangedWeapon) {
		rangedWeapon->reload();
	}
	Melee* meleeWeapon = dynamic_cast<Melee*>(getSelectedWeapon());
	if (meleeWeapon) {
		meleeWeapon->repair();
	}

}

void Character::setReward(bool gotReward)
{
	this->gotReward = gotReward;
}


bool Character::wasRewarded() const
{
	return gotReward;
}

void Character::setFleeing(bool isFleeing)
{
	this->isFleeing = isFleeing;
}

bool Character::getFleeing() const
{
	return isFleeing;
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
		gotReward = false;
		level++;
		xp -= maxXp;
		maxXp = 100 + (level-1)*20;
	}
}

void Character::selectWeapon(unsigned index)
{
	if (index >= weapons.size()) {
		cout << "Invalid weapon index!" << endl;
		return;
	}
	selectedWeaponIndex = index;
	cout << "Selected weapon: " << weapons[selectedWeaponIndex]->getName() << endl;
}

void Character::takeWeapon(Weapon* weapon)
{
	if (weapons.size() >= maxWeaponCount) {
		cout << "Inventory is full! Cannot take more weapons." << endl;
		return;
	}
	if (weapon) {
		weapons.push_back(unique_ptr<Weapon>(weapon));
	}
	else
	{
		cout << "Invalid weapon!" << endl;
	}
}

void Character::dropSelected()
{
	if (weapons.empty() || selectedWeaponIndex >= weapons.size()) {
		cout << "No weapon selected to drop!" << endl;
		return;
	}
	cout << "Dropped weapon: " << weapons[selectedWeaponIndex]->getName() << endl;
	weapons.erase(weapons.begin() + selectedWeaponIndex);
	selectedWeaponIndex = 0;
}

void Character::repairSelected()
{
	if (weapons.empty() || selectedWeaponIndex >= weapons.size()) {
		cout << "No weapon selected to repair!" << endl;
		return;
	}

	Weapon* weapon = weapons[selectedWeaponIndex].get();

	Melee* repairableWeapon = dynamic_cast<Melee*>(weapon);
	if (!repairableWeapon) {
		cout << "There is no need to repair this weapon!" << endl;
		return;
	}

	if (repairableWeapon->isFullyRepaired()) {
		cout << "This weapon is already fully repaired!" << endl;
		return;
	}

	repairableWeapon->repair();

	cout << weapon->getName() << " got repaired." << endl;
}

void Character::clearWeapons()
{
	for (auto& weapon : weapons) {
		weapon.reset();
	}
	weapons.clear();
	selectedWeaponIndex = 0;
}

const vector<unique_ptr<Weapon>>& Character::getWeapons() const
{
	return weapons;
}

Weapon* Character::getSelectedWeapon() const
{
	if (weapons.empty()) {
		cout << "No weapon selected!" << endl;
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

void Character::replaceWeapon(int index, Weapon* newWeapon)
{
	if (index < 0 || index >= weapons.size()) {
		cout << "Invalid weapon index!" << endl;
		return;
	}
	if (newWeapon) {
		weapons[index].reset(newWeapon);
		cout << "Replaced weapon at slot " << index+1 << " with " << newWeapon->getName() << endl;
	}
	else
	{
		cout << "Invalid weapon!" << endl;
	}
}

void Character::displayWeapons() const
{
	if (weapons.empty()) {
		cout << "No weapons in inventory!" << endl;
		return;
	}
	for (size_t i = 0; i < weapons.size(); ++i) {
		cout << i + 1 << ". " << weapons[i]->getName() << endl;
	}
	cout << "Selected weapon: " << weapons[selectedWeaponIndex]->getName() << " (" << selectedWeaponIndex + 1 << ".)" << endl;
}

bool Character::checkLevelUp() const
{
	if(!gotReward) return level % 2 == 0;
	return false;
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
		cout << name << " has no weapon selected to attack!" << endl;
		return;
	}
	if (!target.isAlive()) {
		cout << target.getName() << " is already dead!" << endl;
		return;
	}
	unsigned damage = weapon->getDamage();
	target.changeHealth(-(int)damage);
	weapon->use();
}
