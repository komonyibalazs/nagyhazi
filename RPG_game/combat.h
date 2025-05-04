#pragma once
#include "character.h"

class Combat {
public:
    static void start(Character& player, Character& enemy);

private:
    static void playerTurn(Character& player, Character& enemy);
    static void enemyTurn(Character& enemy, Character& player);

	static bool flee(const Character& player);
	static bool needHeal(Character& player);
	static bool needRepair(Character& player); 
	
	static void displayCombatInfo(const Character& player, const Character& enemy);
	static void displayVictoryMessage(const Character& player);
	static void displayDefeatMessage(const Character& player);
	static void displayFleeMessage(const Character& player);
	static void displayEnemyAttackMessage(const Character& enemy, const Character& player);
	static void displayPlayerAttackMessage(const Character& player, const Character& enemy);
};
