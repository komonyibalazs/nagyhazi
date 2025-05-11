#pragma once
#include "character.h"

class Combat {
public:
    // Harci folyamat ind�t�sa
    static void start(Character& player);
private:
    // Harci k�r kezel�se
    static void enemyTurn(Character& enemy, Character& player);

    // Ellens�g gener�l�sa

    // Harci d�nt�sek
    static bool flee(Character& player);
    static bool needHeal(Character& player);
    static bool needRepair(Character& player);
    static bool changeWeapon(Character& player);

    // Seg�dmet�dusok a harc sor�n
    static void displayCombatInfo(const Character& player, const Character& enemy);
    static void displayVictoryMessage(const Character& player);
    static void displayDefeatMessage(const Character& player);
    static void displayFleeMessage(const Character& player);

    // Harci men� opci�k
    static void fight(Character& player, Character& enemy);
    static void playerTurn(Character& player, Character& enemy);


    // Szintl�p�s ut�ni jutalmak kezel�se
    static void manageLevelUpRewards(Character& player);

    // Kil�p�s meger�s�t�se
    static bool quitGame();
};