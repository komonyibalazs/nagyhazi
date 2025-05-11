#include "combat.h"
#include "menu_manager.h"
#include "input_handler.h"
#include "warrior.h"
#include "wizard.h"
#include "archer.h"
#include <iostream>
#include <string>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()

using namespace std;

void Combat::start(Character& player) {
    srand(static_cast<unsigned>(time(0))); // Véletlenszám generátor seedelése

    while (true) {
        // Generáljunk egy véletlenszerû ellenséget
        Character* enemy = generateRandomEnemy(player.getLevel());
 
        cout << "\nYou are wandering in the wilderness..." << endl;
        cout << endl;
        cout << "-------------------------------------------" << endl;
        cout << "An evil " << enemy->getName() << " (Level " << enemy->getLevel() << ") has appeared!" << endl;

        // Pre-combat menü megjelenítése
        MenuManager::displayPreCombatMenu();
        int preCombatChoice = InputHandler::getIntInput("Choice: ", 1, 3);

        switch (preCombatChoice) {
        case 1: // Ellenség megfigyelése
            
            watchEnemy(player, enemy);
            break;

        case 2: // Vissza a fõmenübe
            delete enemy;
            return;

        case 3: // Kilépés a játékból 
            if (quitGame()) {
                delete enemy;
                exit(0);
            }
            break;

        default:
            MenuManager::displayInvalidChoice();
            delete enemy;
            return;
        }
    }
}

void Combat::watchEnemy(Character& player, Character* enemy) {
    cout << "\nYou chose to take a closer look at the enemy!" << endl;
    displayEnemyInfo(*enemy);

    MenuManager::displayLookMenu();
    int choice = InputHandler::getIntInput("Choice: ", 1, 3);

    if (choice == 1) {
        fight(player, *enemy);
    }
    else if (choice == 2) {
        cout << "\nYou chose to avoid the enemy." << endl;
    }
    else {
        cout << "\nReturning to main menu." << endl;
    }

    delete enemy;
}

void Combat::fight(Character& player, Character& enemy) {
    cout << "The battle begins!" << endl;

    while (true) {
        displayCombatInfo(player, enemy);

        if (!player.isAlive()) {
            displayDefeatMessage(player);
            break;
        }

        if (!enemy.isAlive()) {
            displayVictoryMessage(player);
            player.gainXp(enemy.getLevel() * 10); // Példa XP növelés
            break;
        }

        playerTurn(player, enemy);
        if (enemy.isAlive()) {
            enemyTurn(enemy, player);
        }
    }
}

void Combat::playerTurn(Character& player, Character& enemy)
{
    cout << "Your turn!" << endl;
    while (true)
    {
        MenuManager::displayCombatMenu();
        int choice = InputHandler::getIntInput("Select action: ", 1, 6);
        switch (choice)
        {
        case 1:
            player.attack(enemy);
            return;
        case 2:
            if (needHeal(player)) 
            {
                player.regenerate();
                break;
            }
            else cout << "\nYou don't need to heal!" << endl;
            continue;
        case 3:
            if (flee(player))
            {
                displayFleeMessage(player);
                player.setFleeing(true);
                return;
            }
            continue;
        case 4:
            if (needRepair(player))
            {
                player.repairSelected();
                cout << "\nRepair sucessful!" << endl;
                return;
            }
            else cout << "You can't repair your weapon!" << endl;
            continue;
        case 5:
            if (changeWeapon(player))
            {
                cout << "You have " << player.getWeapons().size() << " weapons." << endl;
                cout << "Current weapon: " << player.getSelectedWeapon()->getName() << "in this slot: " << player.getSelectedIndex() + 1 << endl;
                cout << "Select a weapon slot (1-" << player.getWeapons().size() << "): ";
                int index;
                cin >> index;
                index--;
                if (index < 0 || index >= player.getWeapons().size())
                {
                    cout << "Invalid weapon slot!" << endl;
                    continue;
                }
                player.selectWeapon(index);
                cout << "Weapon changed!" << endl;
                continue;
            }
            else
            {
                cout << "You can't change your weapons!" << endl;
                continue;
            }
            continue;
        case 6:
            MenuManager::displayCharacterInfoMenu();
            int choice = InputHandler::getIntInput("Choice: ", 1, 3);
            while (true)
            {
                switch (choice)
                {

                }
            }
            displayEnemyInfo(enemy);
            continue;
        default:
            MenuManager::displayInvalidChoice();
            continue;
        }
    }
}

void Combat::manageLevelUpRewards(Character& player)
{

    cout << "Congratulations! You've reached level " << player.getLevel() << " and found a new weapon!" << endl;
    Weapon* newWeapon = nullptr;
    string name = "Weapon";
    if (dynamic_cast<Warrior*>(&player))
    {
        int weaponName = rand() % 3;
        switch (weaponName)
        {
        case 0:
            name = "Excalibur Sword";
            break;
        case 1:
            name = "Stormbringer Axe";
            break;
        case 2:
            name = "Mighty Spear";
            break;
        default:
            name = "Unknown Weapon";
            break;
        }
        name += " (Level " + to_string(player.getLevel()) + ")";
        newWeapon = new Melee(name, 20 + (player.getLevel() - 1) * 10, 6 + player.getLevel() - 1);
    }
    else if (dynamic_cast<Wizard*>(&player))
    {
        int weaponName = rand() % 3;
        switch (weaponName)
        {
        case 0:
            name = "Fire Staff";
            break;
        case 1:
            name = "Ice Wand";
            break;
        case 2:
            name = "Lightning Rod";
            break;
        default:
            name = "Unknown Weapon";
            break;
        }
        name += " (Level " + to_string(player.getLevel()) + ")";
        newWeapon = new Magic(name, 20 + (player.getLevel() - 1) * 10, 20 + (player.getLevel() - 1) * 10);
    }
    else if (dynamic_cast<Archer*>(&player))
    {
        int weaponName = rand() % 3;
        switch (weaponName)
        {
        case 0:
            name = "Longbow of the Ancients";
            break;
        case 1:
            name = "Crossbow of Shadows";
            break;
        case 2:
            name = "Swift Bow";
            break;
        default:
            name = "Unknown Weapon";
            break;
        }
        name += " (Level " + to_string(player.getLevel()) + ")";
        newWeapon = new Ranged(name, 20 + (player.getLevel() - 1) * 10, 4 + player.getLevel() - 1);
    }

    if (newWeapon == nullptr)
    {
        cout << "Error: Unable to determine weapon type for this character." << endl;
        return;
    }

    cout << "New weapon: " << newWeapon->getName() << endl;
    cout << "Weapon damage: " << newWeapon->getDamage() << endl;
    while (true)
    {
        if (InputHandler::getYesNoInput("Do you want to add this weapon to your inventory?"))
        {
            if (player.getWeapons().size() < player.getMaxWeaponCount())
            {
                player.takeWeapon(newWeapon);
                cout << "The new weapon has been added to your inventory." << endl;
            }
            else
            {
                cout << "Your weapon slots are full. Choose a weapon to replace: " << endl;
                player.displayWeapons();
                cout << "Enter the slot number (1-" << player.getWeapons().size() << ") to replace: ";
                int slot;
                cin >> slot;
                slot--; // Convert to zero-based index
                if (slot >= 0 && slot < player.getWeapons().size())
                {
                    player.replaceWeapon(slot, newWeapon);
                    cout << "The new weapon has replaced the old one in slot " << (slot + 1) << "." << endl;
                }
                else
                {
                    cout << "Invalid choice. The new weapon has been discarded." << endl;
                    delete newWeapon;
                }
            }
            return;
        }
        else
        {
            cout << "You chose not to add the new weapon." << endl;
            delete newWeapon; // Clean up memory
            return;
        }
    }
}

void Combat::enemyTurn(Character& enemy, Character& player) 
{
    cout << "Enemy's turn!" << endl;
    enemy.attack(player);
}

void Combat::displayEnemyInfo(Character& enemy)
{
    cout << "Enemy:" << endl;
    cout << "Name: " << enemy.getName() << endl;
    cout << "Level: " << enemy.getLevel() << endl;
    cout << "Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
    if(auto* wizard = dynamic_cast<Wizard*>(&enemy))
    {
        cout << "Mana: " << wizard->getMana() << "/" << wizard->getMaxMana() << endl;
    }
    if(auto* warrior = dynamic_cast<Warrior*>(&enemy))
    {
        cout << "Shield: " << warrior->getShield() << "/" << warrior->getMaxShield() << endl;
    }
    cout << "Weapon: " << enemy.getSelectedWeapon()->getName() << endl;
    if(auto* melee = dynamic_cast<Melee*>(enemy.getSelectedWeapon()))
    {
        cout << "Durability: " << melee->getDurability() << "/" << melee->getMaxDurability() << endl;
    }
    if(auto* magic = dynamic_cast<Magic*>(enemy.getSelectedWeapon()))
    {
        cout << "Mana cost: " << magic->getManaCost() << endl;
    }
    if(auto* ranged = dynamic_cast<Ranged*>(enemy.getSelectedWeapon()))
    {
        cout << "Ammo: " << ranged->getAmmo() << "/" << ranged->getMaxAmmo() << endl;
    }
}

void Combat::displayCombatInfo(const Character& player, const Character& enemy) {
    cout << "Player: " << player.getName() << " | Health: " << player.getHealth() << "/" << player.getMaxHp() << endl;
    cout << "Enemy: " << enemy.getName() << " | Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
}

void Combat::displayVictoryMessage(const Character& player) {
    cout << "You have won the battle, " << player.getName() << "!" << endl;
}

void Combat::displayDefeatMessage(const Character& player) {
    cout << "You have been defeated, " << player.getName() << "..." << endl;
}

void Combat::displayFleeMessage(const Character& player)
{
    cout << player.getName() << " has fled from the battle!" << endl;
    displayDefeatMessage(player);
}

Character* Combat::generateRandomEnemy(int playerLevel)
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

bool Combat::flee(Character& player) {
    return InputHandler::getYesNoInput("Do you want to flee the battle?");
}

bool Combat::needHeal(Character& player) {
    return player.getHealth() < player.getMaxHp();
}

bool Combat::needRepair(Character& player)
{
    if(auto* melee = dynamic_cast<Melee*>(player.getSelectedWeapon()))
    {
        return !melee->isFullyRepaired();
    }
    return false;
}

bool Combat::changeWeapon(Character& player) {
    return player.getWeapons().size() > 1;
}

bool Combat::quitGame() {
    return InputHandler::getYesNoInput("Are you sure you want to quit?");
}