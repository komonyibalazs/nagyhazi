#include "melee.h"

using namespace std;

Melee::Melee(string name, unsigned damage, unsigned durability)
	: Weapon(name, damage), durability(durability), maxDurability(durability), sharpness(100)
{
	try {
		if (durability == 0) {
			throw invalid_argument("Melee weapon durability cannot be zero!");
		}
	}
	catch (const invalid_argument& e) {
		cout << e.what() << endl;
		durability = 1;
	}
	catch (const exception& e) {
		cout << "Exception in Melee::Melee: " << e.what() << endl;
	}
	catch (...) {
		cout << "An unknown error occurred!" << endl;
	}
}

Melee::~Melee()
{
}

void Melee::use()
{
	try {
		if (!isBroken())
		{
			cout << "Using " << getName() << " with damage: " << getDamage() << endl;
			sharpness = (sharpness > 0) ? sharpness - 10 : 0;
			durability--;
		}
		else
		{
			throw logic_error("Weapon is broken!");
		}
	}
	catch (const logic_error& e) {
		cout << e.what() << endl;
	}
	catch (const exception& e) {
		cout << "An error occurred: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "An unknown error occurred!" << endl;
	}
}

unsigned Melee::getDamage() const
{
	return damage*sharpness/100;
}

unsigned Melee::getDurability() const
{
	return durability;
}

unsigned Melee::getMaxDurability() const
{
	return maxDurability;
}

unsigned Melee::getSharpness() const
{
	return sharpness;
}

bool Melee::isBroken() const
{
	return durability==0;
}

bool Melee::isFullyRepaired() const
{
	return durability==maxDurability;
}

void Melee::repair()
{
	try
	{
		if (!isFullyRepaired())
		{
			durability = maxDurability;
			sharpness = 100;
		}
		else
		{
			throw logic_error("Weapon is already fully repaired!");
		}
	}
	catch (const logic_error& e) {
		cout << e.what() << endl;
	}
	catch (const exception& e) {
		cout << "An error occurred: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "An unknown error occurred!" << endl;
	}
}
