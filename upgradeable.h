#pragma once
class Upgradeable
{
protected:
	unsigned level;
	unsigned xp;
	unsigned maxXp;
public:
	Upgradeable(unsigned level = 1, unsigned xp = 0, unsigned maxXp = 100);
	virtual ~Upgradeable() = default;
	unsigned getLevel() const;
	unsigned getExperience() const;
	unsigned getMaxExperience() const;
	void gainXp(unsigned gained);
	virtual void levelUp();
};

