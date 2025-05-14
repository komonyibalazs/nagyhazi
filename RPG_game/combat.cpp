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
        // Ellenõrizzük, hogy a játékos vagy az ellenség meghalt-e
        if (!player.isAlive()) {
            displayDefeatMessage(player);
            delete& enemy;
			getchar();
			system("cls");
            Game::handleDefeat(&player);
        }

        if (!enemy.isAlive()) {
            player.wonTheBattle(enemy);
            displayVictoryMessage(player, enemy);
            getchar();
			system("cls");
            if (player.checkLevelUp())
            {
                manageLevelUpRewards(player);       // Szintlépés utáni jutalmak kezelése
            }
            return;
        }

        // Játékos köre
        playerTurn(player, enemy);
		if (player.getFleeing()) {
			player.setFleeing(false);
            return;
		}
        // Ellenség köre, ha még él
        if (enemy.isAlive()) {
			system("cls");
            enemyTurn(enemy, player);
            getchar();
			system("cls");
        }
    }
}

void Combat::playerTurn(Character& player, Character& enemy) {

    while (true) {
        displayCombatInfo(player, enemy);
        MenuManager::displayCombatMenu();
        int choice = InputHandler::getIntInput("Select action: ", 1, 7);

        switch (choice) {
        case 1: // Támadás
			system("cls");
            player.attack(enemy);
            getchar();
            return;

        case 2: // "Heal shield (warrior) és mana regen (wizard)"
			system("cls");
            if (needHeal(player)) {
                player.regenerate();
                cout << "You healed yourself!" << endl;
                getchar();
				system("cls");
                return;
            }
            else {
                cout << "You don't need to heal!" << endl;
                getchar();
            }
			system("cls");
            break;


        case 3: // "Repair or reload"
			system("cls");
            if (needRepair(player)) {
                player.repairSelected();
                cout << "Your weapon has been repaired!" << endl;
                getchar();
				system("cls");
                return;
            }
            else {
                cout << "Your weapon doesn't need repairs!" << endl;
                getchar();
			    system("cls");
                break;
            }

        case 4: // "Flee"
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

        case 5: // "Change weapon"
			system("cls");
            if (changeWeapon(player)) {
                cout << "Choose a new weapon:" << endl;
                player.displayWeapons();
                int index = InputHandler::getIntInput("Select weapon slot: ", 1, player.getWeapons().size());
                player.selectWeapon(--index);
                getchar();
            }
            else {
                cout << "You cannot change weapons right now!" << endl;
                getchar();
            }
			system("cls");
            break;

		case 6: // "Display info"
			system("cls");
			cout << "---------------------------------" << endl;
            cout << endl;
			Game::displayCharacterInfo(player);
			Game::displayWeaponInfo(player);
			Game::displayEnemyInfo(enemy);
			cout << "---------------------------------" << endl;
			getchar();
			system("cls");
            break;

        case 7: // "Skip turn"
            return;
        }
    }
}

void Combat::enemyTurn(Character& enemy, Character& player) {
    cout << "Enemy's turn!" << endl;
    if(auto* weapon = dynamic_cast<Melee*>(enemy.getSelectedWeapon()))
	{
		if (weapon->isBroken())
		{
            weapon->repair();
			cout << "Enemy repaired their weapon!" << endl;
            return;
		}
	}
	else if (auto* weapon = dynamic_cast<Ranged*>(enemy.getSelectedWeapon()))
	{
		if (weapon->isOutOfAmmo())
		{
            weapon->reload();
			cout << "Enemy reloaded their weapon!" << endl;
			cout << endl;
			return;
		}
	}
    enemy.attack(player);
}

void Combat::displayCombatInfo(const Character& player, const Character& enemy) {
    cout << "Player: " << player.getName() << " | Health: " << player.getHealth() << "/" << player.getMaxHp() << endl;
    cout << "Enemy: " << enemy.getName() << " | Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
    cout << endl;
}

void Combat::displayVictoryMessage(const Character& player, const Character& enemy) {
    cout << "You have won the battle, " << player.getName() << "!" << endl;
    cout << endl;
	cout << "+" << enemy.getLevel()*50 << " experience points" << endl;
    cout << endl;
}

void Combat::displayDefeatMessage(const Character& player) {
    cout << "You have been defeated, " << player.getName() << "..." << endl;
    cout << endl;
}

bool Combat::flee(Character& player) {
    return InputHandler::getYesNoInput("Do you want to flee the battle?");
}

bool Combat::needHeal(Character& player) 
{
	if (auto* warrior = dynamic_cast<Warrior*>(&player))
	{
		return player.getHealth() < player.getMaxHp() || warrior->getShield() < warrior->getMaxShield();
	}
	else if (auto* wizard = dynamic_cast<Wizard*>(&player))
	{
		return player.getHealth() < player.getMaxHp() || wizard->getMana() < wizard->getMaxMana();
	}
	else if (auto* archer = dynamic_cast<Archer*>(&player))
	{
		return player.getHealth() < player.getMaxHp();
	}
}

bool Combat::needRepair(Character& player)
{
    if (auto* melee = dynamic_cast<Melee*>(player.getSelectedWeapon()))
    {
        return !melee->isFullyRepaired();
    }
	else if (auto* ranged = dynamic_cast<Ranged*>(player.getSelectedWeapon()))
	{
		return ranged->getAmmo()<ranged->getMaxAmmo();
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
    cout << endl;
	player.setReward(true);
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
    cout << endl;
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
                cout << endl;
                int slot = InputHandler::getIntInput("Enter the slot number (1-" + to_string(player.getWeapons().size()) + ") to replace: ", 1, player.getWeapons().size());
                player.replaceWeapon(slot-1, newWeapon);
                cout << "The new weapon has replaced the old one in slot " << slot << "." << endl;
                cout << endl;
            }
            return;
        }
        else
        {
			system("cls");
            cout << "You chose not to add the new weapon." << endl;
            cout << endl;
            delete newWeapon; // Clean up memory
            return;
        }
    }
}