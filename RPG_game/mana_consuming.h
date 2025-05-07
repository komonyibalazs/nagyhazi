#pragma once
class ManaConsuming
{
public:
	virtual ~ManaConsuming() = default;
	virtual unsigned getManaCost() const = 0;
};

