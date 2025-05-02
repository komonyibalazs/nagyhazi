#pragma once
#include <iostream>

class Weapon
{
protected:
	std::string name;
	unsigned damage;

public:
	Weapon(unsigned damage);
	virtual ~Weapon() = default;

	void setDamage(unsigned damage);
	unsigned getDamage() const;
	virtual void use() = 0;
};

