#pragma once
#include "character.h"

class Combat {
public:
    // Harc elind�t�sa a j�t�kos �s az ellens�g k�z�tt
    static void start(Character& player, Character& enemy);

private:
    // Harci k�r�k kezel�se
    static void playerTurn(Character& player, Character& enemy);
    static void enemyTurn(Character& enemy, Character& player);

    // Inform�ci� ki�r�s a harc sor�n
    static void displayCombatInfo(const Character& player, const Character& enemy);
    static void displayVictoryMessage(const Character& player, const Character& enemy);
    static void displayDefeatMessage(const Character& player);

    // Harci d�nt�sek ellen�rz�se
    static bool flee(Character& player);
    static bool needHeal(Character& player);
    static bool needRepair(Character& player);
    static bool changeWeapon(Character& player);

    // Szintl�p�s ut�ni jutalmak kezel�se
    static void manageLevelUpRewards(Character& player);
};