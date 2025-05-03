#include "upgradeable.h"

Upgradeable::Upgradeable(unsigned level, unsigned xp, unsigned maxXp) : level(level), xp(xp), maxXp(maxXp)
{
	if (level < 1)
	{
		this->level = 1;
	}
	if (xp > maxXp)
	{
		this->xp = xp - maxXp;
	}
}

unsigned Upgradeable::getLevel() const
{
	return level;
}

unsigned Upgradeable::getExperience() const
{
	return xp;
}

unsigned Upgradeable::getMaxExperience() const
{
	return maxXp;
}

void Upgradeable::gainXp(unsigned gained)
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

void Upgradeable::levelUp()
{
	if (xp >= maxXp)
	{
		level++;
		xp -= maxXp;
		maxXp *= 1.1;
	}
}
