#pragma once
#include "character.h"

class Game {
public:
    // A j�t�k elind�t�sa
    static void start();
	// Combat megh�vja csata v�ge ut�n
	static void handleGameOver(Character* player);
    // J�t�k v�ge
    static void end(Character* player);
	// Inform�ci�k ki�r�sa
    static void displayCharacterInfo(Character& player);
    static void displayWeaponInfo(const Character& player);
    static void displayEnemyInfo(Character& enemy);

private:
    // J�t�kos nev�nek bek�r�se
    static std::string getPlayerName();

	// Karakterv�laszt�s
    static void chooseCharacter(Character*& player, const std::string& playerName);
	// Ellens�g gener�l�sa
    static Character* generateRandomEnemy(int playerLevel);
	// Deep Dark pre-combat met�dusok
    static void watchEnemy(Character& player, Character& enemy);
    static void wander(Character& player); 
	// Karakter funkci�k
    static void chooseInformation(Character& player);
	static void managePlayerRepair(Character*& player);
	static void changeWeapon(Character& player);
};