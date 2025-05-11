#include <iostream>
#include <memory>
#include "character.h"
#include "wizard.h"
#include "warrior.h"
#include "archer.h"
#include "combat.h"
#include "main.h"

using namespace std;


void printMenu(const string& name) {
	cout << endl;
    cout << "Welcome " << name << "!\n";
    cout << "Choose your character:\n";
    cout << "\t1. Warrior\n";
    cout << "\t2. Wizard\n";
	cout << "\t3. Archer\n";
    cout << "Choice: ";
}

void chooseCharacter(Character*& player)
{
    while (true)
    {
		string name;
		cout << "Enter your character's name: ";
		cin >> name;
        int choice;
        printMenu(name);
        cin >> choice;
		cout << endl;
        switch (choice)
        {
		case 1:
			player = new Warrior(name);
			cout << "You have chosen the Warrior!" << endl;
			return;
		case 2:
			player = new Wizard(name);
			cout << "You have chosen the Wizard!" << endl;
			return;
		case 3:
			player = new Archer(name);
			cout << "You have chosen the Archer!" << endl;
			return;
		default:
			cout << "Invalid choice. Please try again." << endl;
			continue;
        }

    }
}


/*
TEENDÕK: combat.cpp: check enemy info szarul mûködik. 
*/


int main()
{
	cout << "Welcome to the RPG Game!" << endl;
	Character* player = nullptr;
	chooseCharacter(player);
	Combat::start(*player);
	if (player) {
		delete player;
	}
	return 0;
}

