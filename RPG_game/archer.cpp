#include "archer.h"

using namespace std;

Archer::Archer(const string& name) : Character(name)
{
    try {
        takeWeapon(new Ranged("Bow"));
    }
    catch (const bad_alloc& e) {
        cerr << "Archer constructor: Memory allocation failed for weapon " << e.what() << endl;
        throw; // Re-throw the exception after logging
    }
    catch (const exception& e) {
        cerr << "Exception in Archer constructor: " << e.what() << endl;
        throw;
    }
    catch (...) {
        cerr << "Unknown error occurred in Archer constructor." << endl;
        throw;
    }
}

Archer::Archer(const string& name, unsigned level) : Character(name, level)
{
    try {
        takeWeapon(new Ranged("Bow", 20 + (level - 1) * 10, 4 + level - 1));
    }
    catch (const bad_alloc& e) {
        cerr << "Archer constructor 2: Memory allocation failed for weapon: " << e.what() << endl;
        throw;
    }
    catch (const exception& e) {
        cerr << "Exception in Archer constructor 2: " << e.what() << endl;
        throw;
    }
    catch (...) {
        cerr << "Unknown error occurred in Archer constructor." << endl;
        throw;
    }
}

Archer::~Archer()
{
    try 
    {
        clearWeapons();
    }
    catch (const exception& e) {
        cerr << "Exception in Archer destructor: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error occurred in Archer destructor." << endl;
    }
}

void Archer::regenerate()
{
    try 
    {
        Character::regenerate();
        Ranged* weapon = dynamic_cast<Ranged*>(getSelectedWeapon());
        if (weapon) {
            weapon->reload();
        }
        else 
        {
			throw runtime_error("Selected weapon is not a ranged weapon.");
        }
    }
    catch (const runtime_error& e) {
        cerr << "Exception in Archer::regenerate: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error occurred in Archer::regenerate." << endl;
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