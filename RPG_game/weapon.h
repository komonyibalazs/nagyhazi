#pragma once
#include <iostream>

class Weapon
{
protected:
	std::string name;
	unsigned damage;
	
public:
	Weapon(std::string name, int damage = 10);
	virtual ~Weapon() = default;

	std::string getName() const;

	virtual unsigned getDamage() const;
	virtual void use() = 0;
};

