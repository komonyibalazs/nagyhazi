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
            wander(*player);
            break;

        case 2: // "Reload/repair or regenerate"
			system("cls");
			managePlayerRepair(player);
            break;
        case 3: // "Change weapon"
            system("cls");
            changeWeapon(*player);
            break;


        case 4: // "Check your info"
			system("cls");
            chooseInformation(*player);
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
            (void)getchar();
            system("cls");
            return;
        case 2:
			system("cls");
            player = new Wizard(playerName);
            cout << "You have chosen the Wizard!" << endl;
            (void)getchar();
            system("cls");
            return;
        case 3:
			system("cls");
            player = new Archer(playerName);
            cout << "You have chosen the Archer!" << endl;
            (void)getchar();
            system("cls");
            return;
        }
        
    }
}

void Game::wander(Character& player) {
    // Generáljunk egy random ellenséget
    // Pre-combat menu
    Character* enemy = generateRandomEnemy(player.getLevel());
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
            watchEnemy(player, *enemy);
            delete enemy;
            enemy = generateRandomEnemy(player.getLevel());
            continue;
		
        case 2: // "Check your character information"
			system("cls");
			chooseInformation(player);
			break;

        case 3: // "Back to menu"
            system("cls");
            delete enemy;
            return;
        }
    }
}

void Game::chooseInformation(Character& player)
{
	while (true) {
		MenuManager::displayCharacterInfoMenu();
		int choice = InputHandler::getIntInput("Choice: ", 1, 4);
		switch (choice) {
		case 1: // "Check character"
			system("cls");
			displayCharacterInfo(player);
			break;
		case 2: // "Check weapon"
			system("cls");
			displayWeaponInfo(player);
			break;
		case 3: // "Display inventory"
			system("cls");
			MenuManager::displayInventoryMenu();
			player.displayWeapons(); // Fegyverek megjelenítése
			break;
		case 4: // "Back to menu"
			system("cls");
			return;
		}
	}
    cout << endl;
}

void Game::managePlayerRepair(Character*& player)
{
	if (auto melee = dynamic_cast<Melee*>(player->getSelectedWeapon()))
	{
		if (!melee->isFullyRepaired())
		{
			melee->repair();
			cout << "Weapon repaired!" << endl;
        }
		else
		{
			cout << "Your weapon doesn't need repairs!" << endl;
		}
	}
	else if (auto* ranged = dynamic_cast<Ranged*>(player->getSelectedWeapon()))
	{
		if (ranged->getAmmo() < ranged->getMaxAmmo())
		{
			ranged->reload();
			cout << "Weapon reloaded!" << endl;
		}
		else
		{
			cout << "Your weapon doesn't need reloading!" << endl;
		}
	}

	if (auto* wizard = dynamic_cast<Wizard*>(player))
	{
		if (wizard->getHealth() < wizard->getMaxHp() || wizard->getMana() < wizard->getMaxMana())
		{
			wizard->regenerate();
			cout << "Health and mana regenerated!" << endl;
		}
		else
		{
			cout << "You don't need to regenerate right now!" << endl;
		}
	}
    else if (auto* warrior = dynamic_cast<Warrior*>(player))
	{
		if (warrior->getShield() < warrior->getMaxShield())
		{
			warrior->regenerate();
			cout << "Health and shield regenerated!" << endl;
		}
		else
		{
			cout << "Your shield doesn't need any repair!" << endl;
	    }
	}
	else if (auto* archer = dynamic_cast<Archer*>(player))
	{
		if (archer->getHealth() < archer->getMaxHp())
		{
			archer->regenerate();
			cout << "Health regenerated!" << endl;
		}
	}
	cout << endl;
    (void)getchar();
	system("cls");
}

void Game::changeWeapon(Character& player)
{
    try
    {
        if (player.getSelectedIndex() >= player.getMaxWeaponCount())
        {
            throw out_of_range("Invalid weapon index.");
        }
        if (player.getWeapons().size() < 0)
        {
            throw invalid_argument("Weapons size is less than 0.");
        }
        if (player.getWeapons().size() > 1)
        {
            cout << "Choose a new weapon:" << endl;
            player.displayWeapons();
            int index = InputHandler::getIntInput("Select weapon slot: ", 1, static_cast<int>(player.getWeapons().size()));
            player.selectWeapon(--index);
            (void)getchar();
        }
        else
        {
            cout << "You cannot change weapons right now!" << endl;
            (void)getchar();
        }
        system("cls");
    }
    catch (const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
        system("cls");
    }
    catch (const invalid_argument& e)
    {
        cout << "Error: " << e.what() << endl;
        system("cls");
    }
}

void Game::watchEnemy(Character& player, Character& enemy) {
    cout << "You chose to take a closer look at the enemy!" << endl;
    cout << endl;
    displayEnemyInfo(enemy);
    MenuManager::displayLookMenu();
    int choice = InputHandler::getIntInput("Choice: ", 1, 2);

    switch (choice) {
	case 1: // "Fight the enemy"
		system("cls");
        Combat::start(player, enemy);
        break;
	case 2: // "Go deeper"
        system("cls");
        cout << "You chose to avoid the enemy." << endl;
        cout << endl;
		break;
    }
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

void Game::displayCharacterInfo(Character& player) {
    cout << "Your character:" << endl;
    cout << "Name: " << player.getName() << endl;
    cout << "Health: " << player.getHealth() << "/" << player.getMaxHp() << endl;
    cout << "Level: " << player.getLevel() << endl;
    cout << "Experience: " << player.getExperience() << "/" << player.getMaxExperience() << endl;

    if (auto* wizard = dynamic_cast<Wizard*>(&player)) {
        cout << "Class: Wizard" << endl;
        cout << "Mana: " << wizard->getMana() << "/" << wizard->getMaxMana() << endl;
    }
    else if (auto* warrior = dynamic_cast<Warrior*>(&player)) {
        cout << "Class: Warrior" << endl;
        cout << "Shield: " << warrior->getShield() << "/" << warrior->getMaxShield() << endl;
    }
    else if (auto* archer = dynamic_cast<Archer*>(&player)) {
        cout << "Class: Archer" << endl;
    }

    if (player.getSelectedWeapon()) {
        cout << "Current weapon: " << player.getSelectedWeapon()->getName() << endl;
        cout << "Damage: " << player.getSelectedWeapon()->getDamage() << endl;
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
		cout << "Sharpness: " << melee->getSharpness() << "/" << 100 << endl;
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

void Game::handleGameOver(Character* player) {
    while (true) 
    {
        
        MenuManager::displayDefeatMenu();
        int choice = InputHandler::getIntInput("Choice: ", 1, 2);
        switch (choice) 
        {
        case 1: // Új karakter létrehozása és játék újraindítása
            delete player; // Eltávolítjuk a korábbi játékost
			system("cls");
            Game::start();       // Új játék indítása
            return;

        case 2: // Kilépés
            end(player);   // Játék vége funkció meghívása
            exit(0);       // Program bezárása
        }
    }
}

void Game::end(Character* player) {
	system("cls");
    cout << "Game Over. Thank you for playing!" << endl;
    if (player) 
    {
        delete player;
        player = nullptr;
    }
}