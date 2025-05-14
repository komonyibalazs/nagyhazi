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
	xp += gained;
	levelUp();
}

void Character::levelUp()
{
	if (xp >= maxXp)
	{
		gotReward = false;
		level++;
		xp -= maxXp;
		maxXp = level*100;
	}
}

void Character::selectWeapon(unsigned index)
{
	try
	{

		if (index >= weapons.size()) {
			throw out_of_range("Invalid weapon index!");
		}
		selectedWeaponIndex = index;
		system("cls");
		cout << "Selected weapon: " << weapons[selectedWeaponIndex]->getName() << endl;
	}
	catch (const out_of_range& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "An unknown error occurred." << endl;
	}
}

void Character::takeWeapon(Weapon* weapon)
{
	try 
	{
		if (!weapon) {
			throw invalid_argument("Invalid weapon!");
		}
		if (weapons.size() >= maxWeaponCount) {
			throw overflow_error("Weapon vector is bigger than the maximum weapon count!");
		}
		if (weapons.size() == maxWeaponCount) 
		{
			cout << "Inventory is full! Cannot take more weapons." << endl;
		}
		else 
			weapons.push_back(unique_ptr<Weapon>(weapon));
	}
	catch (const invalid_argument & e)
	{
		cout << e.what() << endl;
	}
	catch (const overflow_error& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "An unknown error occurred." << endl;
	}
}

void Character::repairSelected()
{
	try 
	{
		if (selectedWeaponIndex >= weapons.size())
		{
			throw out_of_range("Invalid weapon index!");
		}
		if (weapons.empty())
		{
			cout << "No weapon selected to repair!" << endl;
			return;
		}

		Weapon* weapon = weapons[selectedWeaponIndex].get();
		if (!weapon) 
		{
			cout << "No weapon selected!" << endl;
			return;
		}
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
	}
	catch (const out_of_range& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "An unknown error occurred." << endl;
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
			throw out_of_range("Invalid weapon index!");
		}
		if (!newWeapon) 
		{
			throw invalid_argument("Invalid weapon!");
		}
		weapons[index].reset(newWeapon);
	}
	catch (const out_of_range& e) {
		cout << e.what() << endl;
	}
	catch (const invalid_argument& e) {
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "An unknown error occurred." << endl;
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
