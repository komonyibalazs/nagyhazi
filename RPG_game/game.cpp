#include <iostream>
#include "game.h"
#include "menu_manager.h"
#include "input_handler.h"
#include "combat.h"
#include "warrior.h"
#include "wizard.h"
#include "archer.h"

using namespace std;

void Game::start() {
    // Játékos nevének bekérése
    string name = getPlayerName();
	system("cls");
    // Karakter kiválasztása
    Character* player = nullptr;
    chooseCharacter(player, name);
    while (true) {
        // Fõmenü megjelenítése
        MenuManager::displayMainMenu();
        int choice = InputHandler::getIntInput("Choice: ", 1, 5);

        switch (choice) {
        case 1: // "Wander in the wilderness"
			system("cls");
            wander(player);
            break;

        case 2: // "Check your inventory"
			system("cls");
            MenuManager::displayInventoryMenu();
            player->displayWeapons(); // Fegyverek megjelenítése
            break;

        case 3: // "Check your character info"
			system("cls");
            displayCharacterInfo(player);
            break;

        case 4: // "Check your weapon info"
			system("cls");
            displayWeaponInfo(*player);
            break;

        case 5: // "Quit game"
			system("cls");
            if (InputHandler::getYesNoInput("Are you sure you want to quit?")) 
            {
                end(player);
                return;
            }
			system("cls");
            break;
        }
    }
}

string Game::getPlayerName() {
    return InputHandler::getStringInput("Enter your name: ");
}

void Game::chooseCharacter(Character*& player, const string& playerName) {
    while (true) {
        MenuManager::displayCharacterSelectionMenu(playerName);
        int choice = InputHandler::getIntInput("Choice: ", 1, 3);

        switch (choice) {
        case 1:
			system("cls");
            player = new Warrior(playerName);
            cout << "You have chosen the Warrior!" << endl;
			cout << "(Press Enter to continue...)" << endl;
            getchar();
            system("cls");
            return;
        case 2:
			system("cls");
            player = new Wizard(playerName);
            cout << "You have chosen the Wizard!" << endl;
			cout << "(Press Enter to continue...)" << endl;
            getchar();
            system("cls");
            return;
        case 3:
			system("cls");
            player = new Archer(playerName);
            cout << "You have chosen the Archer!" << endl;
			cout << "(Press Enter to continue...)" << endl;
            getchar();
            system("cls");
            return;
        }
        
    }
}

void Game::watchEnemy(Character& player, Character* enemy) {
    cout << "You chose to take a closer look at the enemy!" << endl;
    cout << endl;
    displayEnemyInfo(*enemy);
    MenuManager::displayLookMenu();
    int choice = InputHandler::getIntInput("Choice: ", 1, 3);

    switch (choice) {
	case 1: // "Fight the enemy"
		system("cls");
        Combat::start(player, *enemy);
        break;
	case 2: // "Go deeper"
        system("cls");
        cout << "You chose to avoid the enemy." << endl;
        cout << endl;
		break;
	case 3: // "return main menu"
		system("cls");
		cout << "Returning to menu." << endl;
		cout << endl;
    }

    delete enemy;
}

Character* Game::generateRandomEnemy(int playerLevel)
{
    int enemyLevel = rand() % playerLevel + 1; // Enemy level between 1 and player's level
    int enemyType = rand() % 3; // Random enemy type
    string enemyName = "Enemy"; // Default name
    switch (enemyType)
    {
    case 0:
        enemyName = "Fallen Warrior";
        return new Warrior(enemyName, enemyLevel);
    case 1:
        enemyName = "Dark Wizard";
        return new Wizard(enemyName, enemyLevel);
    case 2:
        enemyName = "Shadow Archer";
        return new Archer(enemyName, enemyLevel);
    default:
        enemyName = "Unknown Enemy";
        return new Warrior(enemyName, enemyLevel);
    }
}

void Game::wander(Character* player) {
    // Generáljunk egy random ellenséget
    Character* enemy = generateRandomEnemy(player->getLevel());
    // Pre-combat menu
    while (true)
    {
        cout << "You are wandering in the wilderness..." << endl;
        cout << "An evil " << enemy->getName() << " (Level " << enemy->getLevel() << ") has appeared!" << endl;
        cout << endl;
        MenuManager::displayPreCombatMenu();
        int preCombatChoice = InputHandler::getIntInput("Choice: ", 1, 3);

        switch (preCombatChoice) {
        case 1: // "Take a closer look"
            system("cls");
            watchEnemy(*player, enemy);
            return;

        case 2: // "Back to menu"
            system("cls");
            delete enemy;
            return;

        case 3: // "Quit game"
            system("cls");
            if (InputHandler::getYesNoInput("Are you sure you want to quit?")) {
                delete enemy;
                system("cls");
                end(player);
                exit(0);
            }
            system("cls");
            break;
        }
    }
}

void Game::displayCharacterInfo(Character* player) {
    cout << "Your character:" << endl;
    cout << "Name: " << player->getName() << endl;
    cout << "Health: " << player->getHealth() << "/" << player->getMaxHp() << endl;
    cout << "Level: " << player->getLevel() << endl;
    cout << "Experience: " << player->getExperience() << "/" << player->getMaxExperience() << endl;

    if (auto* wizard = dynamic_cast<Wizard*>(player)) {
        cout << "Class: Wizard" << endl;
        cout << "Mana: " << wizard->getMana() << "/" << wizard->getMaxMana() << endl;
    }
    else if (auto* warrior = dynamic_cast<Warrior*>(player)) {
        cout << "Class: Warrior" << endl;
        cout << "Shield: " << warrior->getShield() << "/" << warrior->getMaxShield() << endl;
    }
    else if (auto* archer = dynamic_cast<Archer*>(player)) {
        cout << "Class: Archer" << endl;
    }

    if (player->getSelectedWeapon()) {
        cout << "Current weapon: " << player->getSelectedWeapon()->getName() << endl;
        cout << "Damage: " << player->getSelectedWeapon()->getDamage() << endl;
    }
    else {
        cout << "No weapon selected!" << endl;
    }
    cout << endl;
}

void Game::displayWeaponInfo(const Character& player) {
    cout << "Your current weapon:" << endl;
    cout << "Name: " << player.getSelectedWeapon()->getName() << endl;
    cout << "Damage: " << player.getSelectedWeapon()->getDamage() << endl;
    if (auto* melee = dynamic_cast<Melee*>(player.getSelectedWeapon())) {
        cout << "Durability: " << melee->getDurability() << "/" << melee->getMaxDurability() << endl;
    }
    if (auto* magic = dynamic_cast<Magic*>(player.getSelectedWeapon())) {
        cout << "Mana cost: " << magic->getManaCost() << endl;
    }
    if (auto* ranged = dynamic_cast<Ranged*>(player.getSelectedWeapon())) {
        cout << "Ammo: " << ranged->getAmmo() << "/" << ranged->getMaxAmmo() << endl;
    }
	cout << endl;
}

void Game::displayEnemyInfo(Character& enemy)
{
    cout << "Enemy:" << endl;
    cout << "Name: " << enemy.getName() << endl;
    cout << "Level: " << enemy.getLevel() << endl;
    cout << "Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
    if (auto* wizard = dynamic_cast<Wizard*>(&enemy))
    {
        cout << "Mana: " << wizard->getMana() << "/" << wizard->getMaxMana() << endl;
    }
    if (auto* warrior = dynamic_cast<Warrior*>(&enemy))
    {
        cout << "Shield: " << warrior->getShield() << "/" << warrior->getMaxShield() << endl;
    }
    cout << "Weapon: " << enemy.getSelectedWeapon()->getName() << endl;
    if (auto* melee = dynamic_cast<Melee*>(enemy.getSelectedWeapon()))
    {
        cout << "Durability: " << melee->getDurability() << "/" << melee->getMaxDurability() << endl;
    }
    if (auto* magic = dynamic_cast<Magic*>(enemy.getSelectedWeapon()))
    {
        cout << "Mana cost: " << magic->getManaCost() << endl;
    }
    if (auto* ranged = dynamic_cast<Ranged*>(enemy.getSelectedWeapon()))
    {
        cout << "Ammo: " << ranged->getAmmo() << "/" << ranged->getMaxAmmo() << endl;
    }
	cout << endl;
}

void Game::end(Character*& player) {
	system("cls");
    cout << "Game Over. Thank you for playing!" << endl;
    if (player) {
        delete player;
        player = nullptr;
    }
}