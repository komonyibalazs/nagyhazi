#include "archer.h"

using namespace std;

Archer::Archer(const string& name) : Character(name)
{
    try {
        takeWeapon(new Ranged("Bow"));
    }
    catch (const bad_alloc& e) {
        cerr << "Archer constructor: Memory allocation failed for weapon " << endl;
		cerr << e.what() << endl;
    }
    catch (const exception& e) {
        cerr << "Exception in Archer constructor: " << e.what() << endl;
    }
}

Archer::Archer(const string& name, unsigned level) : Character(name, level)
{
    try {
        takeWeapon(new Ranged("Bow", 20 + (level - 1) * 10, 4 + level - 1));
    }
    catch (const bad_alloc& e) {
        cerr << "Archer constructor 2: Memory allocation failed for weapon: " << e.what() << endl;

    }
    catch (const exception& e) {
        cerr << "Exception in Archer constructor 2: " << e.what() << endl;

    }
}

Archer::~Archer()
{
    clearWeapons();
}

void Archer::regenerate()
{
    Character::regenerate();
    Ranged* weapon = dynamic_cast<Ranged*>(getSelectedWeapon());
    if (weapon) {
        weapon->reload();
    }
    else 
    {
        cout << "Selected weapon is not a ranged weapon." << endl;
    }
}

void Archer::levelUp()
{
    if (xp >= maxXp) 
    {
        maxHp = 100 + level * 50;
        hp = maxHp;
    }
    Character::levelUp();
}