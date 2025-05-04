#include <iostream>
#include <memory>
#include "character.h"
#include "wizard.h"
#include "warrior.h"
#include "archer.h"
#include "combat.h"

using namespace std;

void printMenu() {
    cout << "Welcome traveller!\n";
    cout << "Choose your character:\n";
    cout << "\t1. Warrior\n";
    cout << "\t2. Wizard\n";
    cout << "Choice: ";
}

int main() {
    int choice;
    printMenu();
    cin >> choice;

    unique_ptr<Character> player = nullptr;

    if (choice == 1) {
        string name;
        cout << "Enter your Warrior's name: ";
        cin >> name;
        player = make_unique<Warrior>(name);  
    }
    else if (choice == 2) {
        string name;
        cout << "Enter your Wizard's name: ";
        cin >> name;
        player = make_unique<Wizard>(name);  
    }
    else if (choice == 3) {
        string name;
		cout << "Enter your Archer's name: ";
		cin >> name;
		player = make_unique<Archer>(name);
	}
	else
    {
        cout << "Invalid choice. Exiting.\n";
        return 1;
    }
	Combat combat;
	combat.start(*player, *player);
    return 0;
}

