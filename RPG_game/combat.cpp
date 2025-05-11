#include "combat.h"
#include "menu_manager.h"
#include "input_handler.h"
#include "game.h"
#include "character.h"
#include "warrior.h"
#include "wizard.h"
#include "archer.h"
#include <iostream>
#include <string>

using namespace std;

void Combat::start(Character& player, Character& enemy) {
    cout << "The battle begins!" << endl;
    cout << endl;
    while (true) {
        // Ellen�rizz�k, hogy a j�t�kos vagy az ellens�g meghalt-e
        if (!player.isAlive()) {
            displayDefeatMessage(player);
            break;
        }

        if (!enemy.isAlive()) {
            displayVictoryMessage(player);
			player.changeHealth(player.getMaxHp()); // J�t�kos gy�gy�t�sa
			if (auto* wizard = dynamic_cast<Wizard*>(&player)) wizard->changeMana(wizard->getMaxMana()); // Var�zsl� mana gy�gy�t�sa
			if (auto* warrior = dynamic_cast<Warrior*>(&player)) warrior->setShield(warrior->getMaxShield()); // Harcos pajzs gy�gy�t�sa
            player.gainXp(enemy.getLevel() * 10); // XP n�vel�s az ellens�g szintj�nek f�ggv�ny�ben
            if(player.checkLevelUp())
                manageLevelUpRewards(player);       // Szintl�p�s ut�ni jutalmak kezel�se
            getchar();
			system("cls");
            break;
        }

        // J�t�kos k�re
        playerTurn(player, enemy);
		if (player.getFleeing()) {
			player.setFleeing(false);
            return;
		}
        // Ellens�g k�re, ha m�g �l
        if (enemy.isAlive()) {
			system("cls");
            enemyTurn(enemy, player);
            cout << "(Press Enter to continue...)" << endl;
            getchar();
			system("cls");
        }
    }
}

void Combat::playerTurn(Character& player, Character& enemy) {

    while (true) {
        displayCombatInfo(player, enemy);
        MenuManager::displayCombatMenu();
        int choice = InputHandler::getIntInput("Select action: ", 1, 6);

        switch (choice) {
        case 1: // T�mad�s
			system("cls");
            player.attack(enemy);
            cout << "(Press Enter to continue...)" << endl;
            getchar();
            return;

        case 2: // Gy�gy�t�s
			system("cls");
            if (needHeal(player)) {
                player.regenerate();
                cout << "You healed yourself!" << endl;
                getchar();
            }
            else {
                cout << "You don't need to heal!" << endl;
                getchar();
            }
			system("cls");
            break;

        case 3: // Menek�l�s
			system("cls");
            if (flee(player)) {
				system("cls");
                cout << player.getName() << " fled from the battle!" << endl;
                getchar();
				system("cls");
				player.setFleeing(true);
                return;
            }
			system("cls");
            break;

        case 4: // Fegyver jav�t�sa
			system("cls");
            if (needRepair(player)) {
                player.repairSelected();
                cout << "Your weapon has been repaired!" << endl;
                getchar();
            }
            else {
                cout << "Your weapon doesn't need repairs!" << endl;
				getchar();
            }
			system("cls");
            break;

        case 5: // Fegyver csere
			system("cls");
            if (changeWeapon(player)) {
                cout << "Choose a new weapon:" << endl;
                player.displayWeapons();
                int index = InputHandler::getIntInput("Select weapon slot: ", 1, player.getWeapons().size());
                player.selectWeapon(--index);
                cout << "Weapon changed!" << endl;
                getchar();
            }
            else {
                cout << "You cannot change weapons right now!" << endl;
                getchar();
            }
			system("cls");
            break;

        case 6:
			system("cls");
			cout << "---------------------------------" << endl;
            cout << endl;
			Game::displayCharacterInfo(&player);
			Game::displayWeaponInfo(player);
			Game::displayEnemyInfo(enemy);
			cout << "---------------------------------" << endl;
			getchar();
			system("cls");
            break;
        }
    }
}

void Combat::enemyTurn(Character& enemy, Character& player) {
    cout << "Enemy's turn!" << endl;
    enemy.attack(player);
}

void Combat::displayCombatInfo(const Character& player, const Character& enemy) {
    cout << "Player: " << player.getName() << " | Health: " << player.getHealth() << "/" << player.getMaxHp() << endl;
    cout << "Enemy: " << enemy.getName() << " | Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
    cout << endl;
}

void Combat::displayVictoryMessage(const Character& player) {
    cout << "You have won the battle, " << player.getName() << "!" << endl;
    cout << endl;
}

void Combat::displayDefeatMessage(const Character& player) {
    cout << "You have been defeated, " << player.getName() << "..." << endl;
    cout << endl;
}

bool Combat::flee(Character& player) {
    return InputHandler::getYesNoInput("Do you want to flee the battle?");
}

bool Combat::needHeal(Character& player) {
    return player.getHealth() < player.getMaxHp();
}

bool Combat::needRepair(Character& player)
{
    if (auto* melee = dynamic_cast<Melee*>(player.getSelectedWeapon()))
    {
        return !melee->isFullyRepaired();
    }
    return false;
}

bool Combat::changeWeapon(Character& player) {
    return player.getWeapons().size() > 1;
}

void Combat::manageLevelUpRewards(Character& player)
{
	system("cls");
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
			system("cls");
            if (player.getWeapons().size() < player.getMaxWeaponCount())
            {
                player.takeWeapon(newWeapon);
                cout << "The new weapon has been added to your inventory." << endl;
                cout << endl;
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
                    cout << endl;
                }
                else
                {
                    cout << "Invalid choice. The new weapon has been discarded." << endl;
                    delete newWeapon;
                    cout << endl;
                }
            }
            return;
        }
        else
        {
			system("cls");
            cout << "You chose not to add the new weapon." << endl;
            getchar();
            delete newWeapon; // Clean up memory
            return;
        }
		system("cls");
    }
}