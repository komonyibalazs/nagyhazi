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
	this->maxXp = level*100;
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

void Character::wonTheBattle(const Character& enemy)
{
	gainXp(enemy.getLevel()*50);
	hp = maxHp;
	if(auto* rangedWeapon = dynamic_cast<Ranged*>(getSelectedWeapon()))
	{
		rangedWeapon->reload();
	}
	if (auto* meleeWeapon = dynamic_cast<Melee*>(getSelectedWeapon()))
	{
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
	try 
	{
		if (gained == 0) {
			throw invalid_argument("Gained XP cannot be zero!");
		}
		if (gained > 10000) 
		{
			throw out_of_range("Gained XP is unrealistically high!");
		}

		xp += gained;
		levelUp();
	}
	catch (const invalid_argument& e) {
		cerr << "Invalid Argument Error in gainXp: " << e.what() << endl;
	}
	catch (const out_of_range& e) {
		cerr << "Out of Range Error in gainXp: " << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown error occurred in gainXp." << endl;
	}
}

void Character::levelUp()
{
	try {
		if (xp < maxXp) {
			throw logic_error("Not enough XP to level up!");
		}

		// Szintlépés logikája
		setReward(false);
		level++;
		xp -= maxXp;
		maxXp = level * 100;
		maxHp += 50;
		hp = maxHp;
		cout << "Level up! New level: " << level << endl;
	}
	catch (const logic_error& e) {
		cerr << "Logic Error in levelUp: " << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown error occurred in levelUp." << endl;
	}
}

void Character::selectWeapon(unsigned index)
{
	try {
		if (index >= weapons.size()) {
			throw std::out_of_range("Invalid weapon index!");
		}
		selectedWeaponIndex = index;
		std::cout << "Selected weapon: " << weapons[selectedWeaponIndex]->getName() << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Out of Range Error in selectWeapon: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error occurred in selectWeapon." << std::endl;
	}
}

void Character::takeWeapon(Weapon* weapon)
{
	try {
		if (!weapon) {
			throw std::invalid_argument("Weapon pointer is null!");
		}
		if (weapons.size() >= maxWeaponCount) {
			throw std::overflow_error("Weapon vector exceeds max weapon count!");
		}
		weapons.push_back(std::unique_ptr<Weapon>(weapon));
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid Argument Error in takeWeapon: " << e.what() << std::endl;
	}
	catch (const std::overflow_error& e) {
		std::cerr << "Overflow Error in takeWeapon: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error occurred in takeWeapon." << std::endl;
	}
}

void Character::repairSelected()
{
	try {
		if (selectedWeaponIndex >= weapons.size()) {
			throw std::out_of_range("Invalid weapon index!");
		}

		Weapon* weapon = weapons[selectedWeaponIndex].get();
		if (!weapon) {
			throw std::runtime_error("No weapon selected to repair!");
		}

		Melee* repairableWeapon = dynamic_cast<Melee*>(weapon);
		if (!repairableWeapon) {
			throw std::invalid_argument("Selected weapon is not repairable!");
		}

		if (repairableWeapon->isFullyRepaired()) {
			throw std::logic_error("Weapon is already fully repaired!");
		}

		repairableWeapon->repair();
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Out of Range Error in repairSelected: " << e.what() << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Runtime Error in repairSelected: " << e.what() << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid Argument Error in repairSelected: " << e.what() << std::endl;
	}
	catch (const std::logic_error& e) {
		std::cerr << "Logic Error in repairSelected: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error occurred in repairSelected." << std::endl;
	}
}

void Character::clearWeapons()
{
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
	try {
		if (index < 0 || index >= weapons.size()) {
			throw std::out_of_range("Invalid weapon index!");
		}
		if (!newWeapon) {
			throw std::invalid_argument("New weapon pointer is null!");
		}
		weapons[index].reset(newWeapon);
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Out of Range Error in replaceWeapon: " << e.what() << std::endl;
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid Argument Error in replaceWeapon: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error occurred in replaceWeapon." << std::endl;
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
	cout << endl;
}

bool Character::checkLevelUp() const
{
	if(!gotReward) return level % 2 == 0;
	return false;
}

void Character::regenerate()
{
	if (hp < maxHp && hp+maxHp*0.5 <maxHp)
	{
		hp += maxHp*0.5;
	}
	else
	{
		hp = maxHp;
	}
}

void Character::attack(Character& target)
{
	Weapon* weapon = getSelectedWeapon();
	if (!weapon) 
	{
		cout << name << " has no weapon selected to attack!" << endl;
		return;
	}
	if (auto rangedWeapon = dynamic_cast<Ranged*>(weapon))
	{
		if (rangedWeapon->isOutOfAmmo())
		{
			cout << "Out of ammo!" << endl;
			return;
		}
	}
	else if (auto meleeWeapon = dynamic_cast<Melee*>(weapon))
	{
		if (meleeWeapon->isBroken())
		{
			cout << "Weapon is broken!" << endl;
			return;
		}
	}
	unsigned damage = weapon->getDamage();
	target.changeHealth(-(int)damage);
	weapon->use();
}
