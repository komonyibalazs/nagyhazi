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

    // Karakter kiv�laszt�sa
    static void chooseCharacter(Character*& player, const std::string& playerName);
    //displayInfo
    static void displayCharacterInfo(Character* player);
    static void displayWeaponInfo(const Character& player);
    // J�t�k v�ge
    static void end(Character*& player);
};