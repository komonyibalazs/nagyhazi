#include "magic.h"

using namespace std;

Magic::Magic(string name, unsigned damage, unsigned manaCost) : Weapon(name, damage), manaCost(manaCost)
{
	try {
		if (manaCost == 0) {
			throw invalid_argument("Magic weapon mana cost cannot be zero!");
		}
	}
	catch (const invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		manaCost = 1;
	}
	catch (...) {
		cerr << "An unexpected error occurred." << endl;
	}
}

Magic::~Magic()
{
}

unsigned Magic::getManaCost() const
{
	return manaCost;
}

void Magic::use()
{
	try 
	{
		if (manaCost == 0) {
			throw invalid_argument("Mana cost cannot be zero!");
		}
		cout << "Using " << getName() << " with damage: " << getDamage() << " and mana cost: " << getManaCost() << endl;
	}
	catch (const invalid_argument& e) {
		cerr << "Error: " << e.what() << endl;
		return;
	}
	catch (...) {
		cerr << "An unexpected error occurred." << endl;
		return;
	}
}
