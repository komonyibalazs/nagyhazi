#pragma once
class AmmoConsuming
{
public:
	virtual ~AmmoConsuming() = default;
	virtual unsigned getAmmo() const = 0;
	virtual unsigned getMaxAmmo() const = 0;
	virtual bool isOutOfAmmo() const = 0;
	virtual void reload() = 0;
};

