#include "ranged.h"

using namespace std;

Ranged::Ranged(string name, unsigned damage, unsigned maxAmmo) : Weapon(name, damage), maxAmmo(maxAmmo), ammo(maxAmmo)
{}

void Ranged::use()
{
	if (!isOutOfAmmo())
	{
		cout << "Using " << getName() << " with damage: " << getDamage() << endl;
		ammo--;
	}
	else
	{
		cout << "Out of ammo!" << endl;
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
	if (ammo < maxAmmo)
	{
		ammo = maxAmmo;
	}
	else
	{
		cout << getName() << " is already full!" << endl;
	}
}
