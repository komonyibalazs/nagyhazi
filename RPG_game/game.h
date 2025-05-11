#pragma once
#include <iostream>
#include "combat.h"
#include "character.h"
class Game
{
private:
	static void chooseCharacter(Character*& player);
	static void printMenu(const std::string& name);
	static void end(Character*& player);
public:
	static void start();
};

