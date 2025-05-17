#pragma once
#include "character.h"

class Game {
public:
    // A játék elindítása
    static void start();
	// combat.cpp meghívja csata vége után
    static void wander(Character& player); 
	static void handleGameOver(Character* player);
    // Játék vége
    static void end(Character* player);
    // Display
    static void displayCharacterInfo(Character& player);
    static void displayWeaponInfo(const Character& player);
    static void displayEnemyInfo(Character& enemy);

private:
    // Játékos nevének bekérése
    static std::string getPlayerName();

    // Funkciók
    static void chooseCharacter(Character*& player, const std::string& playerName);
    static Character* generateRandomEnemy(int playerLevel);
	// Deep Dark pre-combat
    static void watchEnemy(Character& player, Character& enemy);
	// Karakter funkciók
    static void chooseInformation(Character& player);
	static void managePlayerRepair(Character*& player);
	static void changeWeapon(Character& player);
};