#include "upgradeable.h"

Upgradeable::Upgradeable(unsigned level, unsigned xp, unsigned maxXp)
{
	this->level = level;
	this->xp = xp;
	this->maxXp = maxXp;
}

unsigned Upgradeable::getLevel() const
{
	return 0;
}

unsigned Upgradeable::getExperience() const
{
	return 0;
}

unsigned Upgradeable::getMaxExperience() const
{
	return 0;
}

void Upgradeable::gainXp(unsigned gained)
{
}
