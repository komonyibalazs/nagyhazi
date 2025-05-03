#pragma once
#include <iostream>

class Weapon
{
protected:
	std::string name;
	unsigned damage;

public:
	Weapon(std::string name, unsigned damage);
	virtual ~Weapon() = default;

	std::string getName() const;
	unsigned getDamage() const;
	virtual void use() = 0;
};

