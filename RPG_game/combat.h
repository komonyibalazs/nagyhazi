#pragma once
#include "character.h"

class Combat {
public:
    // Harc elindítása a játékos és az ellenség között
    static void start(Character& player, Character& enemy);

private:
    // Harci körök kezelése
    static void playerTurn(Character& player, Character& enemy);
    static void enemyTurn(Character& enemy, Character& player);

    // Információ kiírás a harc során
    static void displayCombatInfo(const Character& player, const Character& enemy);
    static void displayVictoryMessage(const Character& player, const Character& enemy);
    static void displayDefeatMessage(const Character& player);

    // Harci döntések ellenõrzése
    static bool flee(Character& player);
    static bool needHeal(Character& player);
    static bool needRepair(Character& player);
    static bool changeWeapon(Character& player);

    // Szintlépés utáni jutalmak kezelése
    static void manageLevelUpRewards(Character& player);
};