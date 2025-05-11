#include "menu_manager.h"
#include <iostream>

using namespace std;

void MenuManager::displayMainMenu() {
    cout << "\nMAIN MENU" << endl;
    cout << "1. Wander in the wilderness" << endl;
    cout << "2. Check your inventory" << endl;
    cout << "3. Check your character info" << endl;
    cout << "4. Check your weapon info" << endl;
    cout << "5. Quit game" << endl;
}

void MenuManager::displayCharacterSelectionMenu(const string& playerName) {
    cout << "\nWelcome " << playerName << "!" << endl;
    cout << "\nChoose your character class:" << endl;
    cout << "1. Warrior" << endl;
    cout << "2. Wizard" << endl;
    cout << "3. Archer" << endl;
}

void MenuManager::displayCombatMenu() {
    cout << "\nCOMBAT MENU" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Heal" << endl;
    cout << "3. Flee" << endl;
    cout << "4. Repair" << endl;
    cout << "5. Change weapon" << endl;
    cout << "6. Display Info" << endl;
}

void MenuManager::displayPreCombatMenu() {
    cout << "\nPRE-COMBAT MENU" << endl;
    cout << "1. Take a closer look" << endl;
    cout << "2. Back to menu" << endl;
    cout << "3. Quit game" << endl;
}

void MenuManager::displayLookMenu()
{
    cout << endl;
    cout << "1. Fight the enemy" << endl;
    cout << "2. Go deeper" << endl;
    cout << "3. Return" << endl;
    cout << "3. Quit game" << endl;
}

void MenuManager::displayInventoryMenu() {
    cout << "\nYour inventory:" << endl;
}

void MenuManager::displayCharacterInfoMenu() {
    cout << "\nCHARACTER INFO MENU" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Display Character Info" << endl;
    cout << "2. Display Weapon Info" << endl;
    cout << "3. Return to Main Menu" << endl;
}

void MenuManager::displayQuitConfirmation() {
    cout << "Are you sure you want to quit? (yes/no): ";
}

void MenuManager::displayInvalidChoice() {
    cout << "Invalid choice. Please try again." << endl;
}