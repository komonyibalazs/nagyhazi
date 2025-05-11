#include "game.h"

using namespace std;

void Game::start()
{
	cout << "Welcome to the RPG Game!" << endl;
	Character* player = nullptr;
	chooseCharacter(player);
	Combat::start(*player);
	end(player);
}

void Game::end(Character*& player)
{
	cout << endl;
	cout << "Game over" << endl;
	if (player) delete player;
}

void Game::chooseCharacter(Character*& player)
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

void Game::printMenu(const string& name)
{
	cout << endl;
	cout << "Welcome " << name << "!\n";
	cout << "Choose your class:\n";
	cout << "\t1. Warrior\n";
	cout << "\t2. Wizard\n";
	cout << "\t3. Archer\n";
	cout << "Choice: ";
}
