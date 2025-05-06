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
        switch (choice)
        {
		case 1:
			player = new Warrior(name, true);
			cout << "You have chosen the Warrior!\n";
			return;
		case 2:
			player = new Wizard(name, true);
			cout << "You have chosen the Wizard!\n";
			return;
		case 3:
			player = new Archer(name, true);
			cout << "You have chosen the Archer!\n";
			return;
		default:
			cout << "Invalid choice. Please try again.\n";
			continue;
        }

    }
}

void testCharacters()
{  
}



void testWeapons()
{
}

int main() 
{
	//testCharacters();
	testWeapons();
	
	
	
    return 0;
}

