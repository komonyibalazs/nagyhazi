#pragma once
#include <string>
#include "character.h"

class Game {
public:
    // A játék elindítása
    static void start();

private:
    // Játékos nevének bekérése
    static std::string getPlayerName();

    // Funkciók
    static void chooseCharacter(Character*& player, const std::string& playerName);
    static Character* generateRandomEnemy(int playerLevel);
    static void watchEnemy(Character& player, Character* enemy);
    static void wander(Character* player);

    //displayInfo
    static void displayCharacterInfo(Character* player);
    static void displayWeaponInfo(const Character& player);
    static void displayEnemyInfo(Character& enemy);
    // Játék vége
    static void end(Character*& player);
};