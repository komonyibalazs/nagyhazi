#pragma once
#include "character.h"
#include "warrior.h"
#include "wizard.h"
#include "archer.h"
#include <string>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()

class Combat {
public:
    static void start(Character& player);

private:
	static void fight(Character& player, Character& enemy);
	static Character* generateRandomEnemy(int playerLevel);
	static void manageLevelUpRewards(Character& player);

    static void playerTurn(Character& player, Character& enemy);
    static void enemyTurn(Character& enemy, Character& player);

	static bool flee(const Character& player);
	static bool needHeal(Character& player);
	static bool needRepair(Character& player); 
	static bool changeWeapon(Character& player);
	
	static void displayCombatInfo(const Character& player, const Character& enemy);
	static void displayVictoryMessage(const Character& player);
	static void displayDefeatMessage(const Character& player);
	static void displayFleeMessage(const Character& player);
	static void displayEnemyAttackMessage(const Character& enemy, const Character& player);
	static void displayPlayerAttackMessage(const Character& player, const Character& enemy);
};
