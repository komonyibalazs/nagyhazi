#pragma once
class Repairable 
{
protected:
	unsigned durability;
	unsigned maxDurability;
public:
	Repairable(unsigned maxDurability);
    virtual ~Repairable() = default;
	unsigned getDurability() const;
    virtual void repair() = 0;
};

