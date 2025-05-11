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
    // J�t�kos nev�nek bek�r�se
    string name = getPlayerName();

    // Karakter kiv�laszt�sa
    Character* player = nullptr;
    chooseCharacter(player, name);

    while (true) {
        // F�men� megjelen�t�se
        MenuManager::displayMainMenu();
        int choice = InputHandler::getIntInput("Choice: ", 1, 5);

        switch (choice) {
        case 1: // J�t�k ind�t�sa
            Combat::start(*player); // Harci logika elind�t�sa
            break;

        case 2: // Inventory megtekint�se
            MenuManager::displayInventoryMenu();
            player->displayWeapons(); // Karakter fegyvereinek megjelen�t�se (felt�telezett met�dus)
            break;

        case 3: // Karakterinform�ci�k megtekint�se
            displayCharacterInfo(player);
            break;

        case 4: // Fegyverinform�ci�k megtekint�se
            displayWeaponInfo(*player);
            break;

        case 5: // Kil�p�s
            if (InputHandler::getYesNoInput("Are you sure you want to quit?")) {
                end(player);
                return;
            }
            break;

        default:
            MenuManager::displayInvalidChoice();
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
            player = new Warrior(playerName);
            cout << "\nYou have chosen the Warrior!" << endl;
            return;
        case 2:
            player = new Wizard(playerName);
            cout << "\nYou have chosen the Wizard!" << endl;
            return;
        case 3:
            player = new Archer(playerName);
            cout << "\nYou have chosen the Archer!" << endl;
            return;
        default:
            MenuManager::displayInvalidChoice();
            break;
        }
    }
}

void Game::displayCharacterInfo(Character* player) {
    cout << "\nYour character:" << endl;
    cout << "Name: " << player->getName() << endl;
    cout << "Health: " << player->getHealth() << "/" << player->getMaxHp() << endl;
    cout << "Level: " << player->getLevel() << endl;
    cout << "Experience: " << player->getExperience() << "/" << player->getMaxExperience() << endl;

    if (auto* wizard = dynamic_cast<Wizard*>(player)) {
        cout << "Class: wizard" << endl;
        cout << "Mana: " << wizard->getMana() << "/" << wizard->getMaxMana() << endl;
    }
    else if (auto* warrior = dynamic_cast<Warrior*>(player)) {
        cout << "Class: warrior" << endl;
        cout << "Shield: " << warrior->getShield() << "/" << warrior->getMaxShield() << endl;
    }
    else if (auto* archer = dynamic_cast<Archer*>(player)) {
        cout << "Class: archer" << endl;
    }

    if (player->getSelectedWeapon()) {
        cout << "Current weapon: " << player->getSelectedWeapon()->getName() << endl;
        cout << "Damage: " << player->getSelectedWeapon()->getDamage() << endl;
    }
    else {
        cout << "No weapon selected!" << endl;
    }
}

void Game::displayWeaponInfo(const Character& player)
{
    cout << "\nYour current weapon:" << endl;
    cout << "Name: " << player.getSelectedWeapon()->getName() << endl;
    cout << "Damage: " << player.getSelectedWeapon()->getDamage() << endl;
    if(auto* melee = dynamic_cast<Melee*>(player.getSelectedWeapon()))
    {
        cout << "Durability: " << melee->getDurability() << "/" << melee->getMaxDurability() << endl;
    }
    if (auto* magic = dynamic_cast<Magic*>(player.getSelectedWeapon()))
    {
        cout << "Mana cost: " << magic->getManaCost() << endl;
    }
    if(auto* ranged = dynamic_cast<Ranged*>(player.getSelectedWeapon()))
    {
        cout << "Ammo: " << ranged->getAmmo() << "/" << ranged->getMaxAmmo() << endl;
    }
}

void Game::end(Character*& player) {
    cout << "\nGame Over. Thank you for playing!" << endl;
    if (player) {
        delete player;
        player = nullptr;
    }
}