#include "ranged.h"

using namespace std;

Ranged::Ranged(string name, unsigned damage, unsigned maxAmmo) : Weapon(name, damage), maxAmmo(maxAmmo), ammo(maxAmmo)
{
	try 
	{
		if (maxAmmo == 0) {
			throw invalid_argument("Ranged weapon max ammo cannot be zero!");
		}
	}
	catch (const invalid_argument& e)
	{
		cerr << "Error: " << e.what() << endl;
		maxAmmo = 1;
	}
	catch (const exception& e)
	{
		cerr << "Exception in Ranged::Ranged: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "An unknown error occurred." << endl;
	}
}


void Ranged::use()
{
	try {
		if (isOutOfAmmo())
		{
			throw logic_error("Out of ammo!");
		}
		cout << "Using " << getName() << " with damage: " << getDamage() << endl;
		ammo--;
	}
	catch (const logic_error& e)
	{
		cerr << e.what() << endl;
	}
	catch (const exception& e)
	{
		cerr << "Exception in Ranged::use: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "An unknown error occurred." << endl;
	}
}

unsigned Ranged::getAmmo() const
{
    return ammo;
}

unsigned Ranged::getMaxAmmo() const
{
	return maxAmmo;
}

bool Ranged::isOutOfAmmo() const
{
	return ammo==0;
}

void Ranged::reload()
{
	try {
		if (ammo < maxAmmo)
		{
			ammo = maxAmmo;
		}
		else
		{
			throw logic_error(getName() + " is already full!");
		}
	}
	catch (const logic_error& e)
	{
		cerr << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Exception in Ranged::reload: " << e.what() << endl;
	}
	catch (...)
	{
		cerr << "An unknown error occurred." << endl;
	}
}
