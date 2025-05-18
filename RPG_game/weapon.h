#pragma once
#include <iostream>

class Weapon
{
protected:
	std::string name;
	unsigned damage;
	
public:
	// Konstruktor, destruktor
	Weapon(std::string name, int damage = 20);
	virtual ~Weapon() = default;
	// getter
	std::string getName() const;
	
	// virtuális metódusok
	virtual unsigned getDamage() const;
	virtual void use() = 0;
};

