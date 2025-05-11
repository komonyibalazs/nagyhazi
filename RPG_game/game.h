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

    // Karakter kiválasztása
    static void chooseCharacter(Character*& player, const std::string& playerName);
    //displayInfo
    static void displayCharacterInfo(Character* player);
    static void displayWeaponInfo(const Character& player);
    // Játék vége
    static void end(Character*& player);
};