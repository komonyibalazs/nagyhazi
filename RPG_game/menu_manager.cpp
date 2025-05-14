#include "menu_manager.h"
#include <iostream>

using namespace std;

void MenuManager::displayMainMenu() {
    cout << "BASE" << endl;
    cout << "1. Wander in the wilderness" << endl;
	cout << "2  Reload, repair and regenerate" << endl;
	cout << "3. Change weapon" << endl;
    cout << "4. Check your character information" << endl;
    cout << "5. Quit game" << endl;
}

void MenuManager::displayCharacterSelectionMenu(const string& playerName) {
    cout << "Welcome " << playerName << "!" << endl;
    cout << endl;
    cout << "Choose your character class:" << endl;
    cout << "1. Warrior" << endl;
    cout << "2. Wizard" << endl;
    cout << "3. Archer" << endl;
}

void MenuManager::displayCombatMenu() {
    cout << "Your turn!" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Regenerate" << endl;
    cout << "3. Repair or reload" << endl;
    cout << "4. Flee" << endl;
    cout << "5. Change weapon" << endl;
    cout << "6. Display Info" << endl;
    cout << "7. Skip trun" << endl;
}

void MenuManager::displayPreCombatMenu() {
    cout << "DEEP DARK" << endl;
    cout << "1. Take a closer look" << endl;
	cout << "2. Check your character information" << endl;
    cout << "3. Back to menu" << endl;
}

void MenuManager::displayLookMenu()
{
	cout << "DEEP DARK" << endl;
    cout << "1. Fight!" << endl;
    cout << "2. Go deeper" << endl;
}

void MenuManager::displayInventoryMenu() {
    cout << "Your inventory:" << endl;
}

void MenuManager::displayCharacterInfoMenu() {
    cout << "INFO" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Check character" << endl;
    cout << "2. Check weapon" << endl;
	cout << "3. Display inventory" << endl;
    cout << "4. Back" << endl;
}

void MenuManager::displayQuitConfirmation() {
    cout << "Are you sure you want to quit? (yes/no): ";
}

void MenuManager::displayInvalidChoice() {
    cout << "Invalid choice. Please try again." << endl;
}

void MenuManager::displayDefeatMenu() {
    cout << "What would you like to do?" << endl;
    cout << "1. Start again" << endl;
    cout << "2. Quit the game" << endl;
}