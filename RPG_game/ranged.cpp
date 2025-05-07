#include "ranged.h"

Ranged::Ranged(std::string name, unsigned damage, unsigned maxAmmo) : Weapon(name, damage), maxAmmo(maxAmmo), ammo(maxAmmo)
{}

void Ranged::use()
{
	if (!isOutOfAmmo())
	{
		std::cout << "Using " << getName() << " with damage: " << getDamage() << std::endl;
		ammo--;
	}
	else
	{
		std::cout << "Out of ammo!" << std::endl;
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
		std::cout << "Reloading " << getName() << " to max ammo: " << maxAmmo << std::endl;
	}
	else
	{
		std::cout << getName() << " is already full!" << std::endl;
	}
}
