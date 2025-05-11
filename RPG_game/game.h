#pragma once
#include <string>
#include "character.h"

class Game {
public:
    // A j�t�k elind�t�sa
    static void start();

private:
    // J�t�kos nev�nek bek�r�se
    static std::string getPlayerName();

    // Funkci�k
    static void chooseCharacter(Character*& player, const std::string& playerName);
    static Character* generateRandomEnemy(int playerLevel);
    static void watchEnemy(Character& player, Character* enemy);
    static void wander(Character* player);

    //displayInfo
    static void displayCharacterInfo(Character* player);
    static void displayWeaponInfo(const Character& player);
    static void displayEnemyInfo(Character& enemy);
    // J�t�k v�ge
    static void end(Character*& player);
};