#pragma once
#include<iostream>

class InputHandler
{
public:
    // Eg�sz sz�m bemenet kezel�se (minimum �s maximum �rt�kek k�z�tt)
    static int getIntInput(const std::string& prompt, int min, int max);

    // Sz�veges bemenet kezel�se
    static std::string getStringInput(const std::string& prompt);

    // Igen/nem t�pus� bemenet kezel�se
    static bool getYesNoInput(const std::string& prompt);

};

