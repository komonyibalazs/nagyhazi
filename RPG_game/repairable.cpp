#include "repairable.h"

Repairable::Repairable(unsigned maxDurability) : durability(maxDurability), maxDurability(maxDurability)
{}

unsigned Repairable::getDurability() const
{
    return durability;
}

bool Repairable::isBroken() const
{
    return durability==0;
}

bool Repairable::isFullyRepaired() const
{
    return durability==maxDurability;
}
