#pragma once
#include <string>
#include "character.h"

class Game {
public:
    // A j�t�k elind�t�sa
    static void start();
    // Display
    static void displayCharacterInfo(Character& player);
    static void displayWeaponInfo(const Character& player);
    static void displayEnemyInfo(Character& enemy);
	static void handleDefeat(Character* player);

private:
    // J�t�kos nev�nek bek�r�se
    static std::string getPlayerName();

    // Funkci�k
    static void chooseCharacter(Character*& player, const std::string& playerName);
    static Character* generateRandomEnemy(int playerLevel);
	// Deep Dark pre-combat
    static void wander(Character& player);
    static void watchEnemy(Character& player, Character& enemy);
	// Karakter funkci�k
    static void chooseInformation(Character& player);
	static void managePlayerRepair(Character*& player);
	static void changeWeapon(Character& player);
    // J�t�k v�ge
    static void end(Character* player);
};