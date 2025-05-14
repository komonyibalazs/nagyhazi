#pragma once
#include <iostream>

class MenuManager
{
public:
    // Fõmenü megjelenítése
    static void displayMainMenu();

    // Karakterválasztó menü megjelenítése
    static void displayCharacterSelectionMenu(const std::string& playerName);

    // Harci menü megjelenítése
    static void displayCombatMenu();

    // Pre-combat, pl. ellenség megtekintés vagy harc opciók
    static void displayPreCombatMenu();

    static void displayLookMenu();

    // Inventory menü
    static void displayInventoryMenu();

    // Karakterinformációk menü
    static void displayCharacterInfoMenu();

    // Kilépés megerõsítése
    static void displayQuitConfirmation();

    // Érvénytelen választás hibaüzenet
    static void displayInvalidChoice();

    static void displayDefeatMenu();
};

