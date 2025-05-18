#pragma once
#include "character.h"

class Game {
public:
    // A játék elindítása
    static void start();
	// Combat meghívja csata vége után
	static void handleGameOver(Character* player);
    // Játék vége
    static void end(Character* player);
	// Információk kiírása
    static void displayCharacterInfo(Character& player);
    static void displayWeaponInfo(const Character& player);
    static void displayEnemyInfo(Character& enemy);

private:
    // Játékos nevének bekérése
    static std::string getPlayerName();

	// Karakterválasztás
    static void chooseCharacter(Character*& player, const std::string& playerName);
	// Ellenség generálása
    static Character* generateRandomEnemy(int playerLevel);
	// Deep Dark pre-combat metódusok
    static void watchEnemy(Character& player, Character& enemy);
    static void wander(Character& player); 
	// Karakter funkciók
    static void chooseInformation(Character& player);
	static void managePlayerRepair(Character*& player);
	static void changeWeapon(Character& player);
};