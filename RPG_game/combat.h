#pragma once
#include "character.h"

class Combat {
public:
    // Harci folyamat indítása
    static void start(Character& player);
private:
    // Harci kör kezelése
    static void enemyTurn(Character& enemy, Character& player);

    // Ellenség generálása

    // Harci döntések
    static bool flee(Character& player);
    static bool needHeal(Character& player);
    static bool needRepair(Character& player);
    static bool changeWeapon(Character& player);

    // Segédmetódusok a harc során
    static void displayCombatInfo(const Character& player, const Character& enemy);
    static void displayVictoryMessage(const Character& player);
    static void displayDefeatMessage(const Character& player);
    static void displayFleeMessage(const Character& player);

    // Harci menü opciók
    static void fight(Character& player, Character& enemy);
    static void playerTurn(Character& player, Character& enemy);


    // Szintlépés utáni jutalmak kezelése
    static void manageLevelUpRewards(Character& player);

    // Kilépés megerõsítése
    static bool quitGame();
};