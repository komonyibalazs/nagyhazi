#pragma once
#include <iostream>

class MenuManager
{
public:
    // F�men� megjelen�t�se
    static void displayMainMenu();

    // Karakterv�laszt� men� megjelen�t�se
    static void displayCharacterSelectionMenu(const std::string& playerName);

    // Harci men� megjelen�t�se
    static void displayCombatMenu();

    // Pre-combat, pl. ellens�g megtekint�s vagy harc opci�k
    static void displayPreCombatMenu();

    static void displayLookMenu();

    // Inventory men�
    static void displayInventoryMenu();

    // Karakterinform�ci�k men�
    static void displayCharacterInfoMenu();

    // Kil�p�s meger�s�t�se
    static void displayQuitConfirmation();

    // �rv�nytelen v�laszt�s hiba�zenet
    static void displayInvalidChoice();

    static void displayDefeatMenu();
};

