#pragma once
class Repairable 
{
public:
    virtual ~Repairable() = default;
	virtual unsigned getDurability() const = 0;
	virtual bool isBroken() const = 0;
	virtual bool isFullyRepaired() const = 0;
    virtual void repair() = 0;
};

