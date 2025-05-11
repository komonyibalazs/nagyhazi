#pragma once
#include<iostream>

class InputHandler
{
public:
    // Egész szám bemenet kezelése (minimum és maximum értékek között)
    static int getIntInput(const std::string& prompt, int min, int max);

    // Szöveges bemenet kezelése
    static std::string getStringInput(const std::string& prompt);

    // Igen/nem típusú bemenet kezelése
    static bool getYesNoInput(const std::string& prompt);

};

