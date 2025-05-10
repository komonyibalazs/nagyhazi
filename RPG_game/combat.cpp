#include "combat.h"

using namespace std;

void Combat::start(Character& player)
{
	srand(static_cast<unsigned>(time(0))); // Seed a random generator

	while (true)
	{
		// Generate a random enemy whose level is equal to or below the player's level
		Character* enemy = generateRandomEnemy(player.getLevel());
		
		cout << "An evil " << enemy->getName() << " (Level " << enemy->getLevel() << ") has appeared!" << endl;

		// Pre-combat menu
		cout << "1. Fight the enemy" << endl;
		cout << "2. Skip this enemy" << endl;
		cout << "Choice: ";
		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "You chose to fight the enemy!" << endl;
			fight(player, *enemy); // Start combat
			if (player.getHealth() <= 0)
			{
				cout << "Game Over! You have been defeated." << endl;
				delete enemy; // Clean up memory
				return;
			}
			break;
		case 2:
			cout << "You chose to skip this enemy." << endl;
			delete enemy; // Clean up memory
			continue;
		default:
			cout << "Invalid choice. Please try again." << endl;
			continue;
		}

		// Check for level-up rewards
		if (player.checkLevelUp())
		{
			manageLevelUpRewards(player);
		}

		// Check if the player wants to continue playing
		cout << "Do you want to continue your adventure? (yes/no): ";
		string response;
		cin >> response;
		if (response == "no")
		{
			cout << "Thanks for playing!" << endl;
			break;
		}
	}
}

Character* Combat::generateRandomEnemy(int playerLevel)
{
	int enemyLevel = rand() % playerLevel + 1; // Enemy level between 1 and player's level
	int enemyType = rand() % 3; // Random enemy type
	string enemyName = "Enemy"; // Default name
	switch (enemyType)
	{
	case 0:
		enemyName = "Fallen Warrior";
		return new Warrior(enemyName, enemyLevel);
	case 1:
		enemyName = "Dark Wizard";
		return new Wizard(enemyName, enemyLevel);
	case 2:
		enemyName = "Shadow Archer";
		return new Archer(enemyName, enemyLevel);
	default:
		enemyName = "Unknown Enemy";
		return new Warrior(enemyName, enemyLevel);
	}
}

void Combat::manageLevelUpRewards(Character& player)
{
	
		cout << "Congratulations! You've reached level " << player.getLevel() << " and found a new weapon!" << endl;
		Weapon* newWeapon = nullptr;
		if (dynamic_cast<Warrior*>(&player))
		{
			newWeapon = new Melee("Sword", 20 + (player.getLevel() - 1) * 10, 6 + player.getLevel() - 1);
		}
		else if (dynamic_cast<Wizard*>(&player))
		{
			newWeapon = new Magic("Staff", 20 + (player.getLevel() - 1) * 10, 20 + (player.getLevel() - 1) * 10);
		}
		else if (dynamic_cast<Archer*>(&player))
		{
			newWeapon = new Ranged("Bow", 20 + (player.getLevel() - 1) * 10, 4 + player.getLevel() - 1);
		}

		if (newWeapon == nullptr)
		{
			cout << "Error: Unable to determine weapon type for this character." << endl;
			return;
		}

		cout << "New weapon: " << newWeapon->getName() << endl;
		cout << "Weapon damage: " << newWeapon->getDamage() << endl;
		while (true)
		{
			cout << "Do you want to add this weapon to your inventory? (yes/no): ";
			string response;
			cin >> response;
			if (response == "no")
			{
				cout << "You chose not to add the new weapon." << endl;
				delete newWeapon; // Clean up memory
				return;
			}
			else if (response == "yes")
			{
				if (player.getWeapons().size() < player.getMaxWeaponCount())
				{
					player.takeWeapon(newWeapon);
					cout << "The new weapon has been added to your inventory." << endl;
				}
				else
				{
					cout << "Your weapon slots are full. Choose a weapon to replace: " << endl;
					player.displayWeapons();
					cout << "Enter the slot number (1-" << player.getWeapons().size() << ") to replace: ";
					int slot;
					cin >> slot;
					slot--; // Convert to zero-based index
					if (slot >= 0 && slot < player.getWeapons().size())
					{
						player.replaceWeapon(slot, newWeapon);
						cout << "The new weapon has replaced the old one in slot " << (slot + 1) << "." << endl;
					}
					else
					{
						cout << "Invalid choice. The new weapon has been discarded." << endl;
						delete newWeapon;
					}
				}
				return;
			}
			else
			{
				cout << "Invalid choice. Please enter 'yes' or 'no'." << endl;
				continue;
			}
		}
}

void Combat::fight(Character& player, Character& enemy)
{
	cout << "Fight!" << endl;

	while (true)
	{
		displayCombatInfo(player, enemy);

		if (player.getHealth() <= 0)
		{
			displayDefeatMessage(player);
			break;
		}

		if (enemy.getHealth() <= 0)
		{
			player.gainXp(enemy.getMaxExperience()*0.5);
			player.changeHealth(player.getMaxHp());
			displayVictoryMessage(player);
			break;
		}

		playerTurn(player, enemy);
		if (enemy.getHealth() > 0)
		{
			enemyTurn(enemy, player);
		}
	}
}

void Combat::playerTurn(Character& player, Character& enemy)
{
	int choice;
	while (true)
	{
		cout << "-------------------------------------------" << endl;
		cout << "Your turn!" << endl;
		cout << "1. Attack" << endl;
		cout << "2. Heal" << endl;
		cout << "3. Flee" << endl;
		cout << "4. Repair" << endl;
		cout << "5. Change weapon" << endl;
		cout << "6. Display Info" << endl;
		cout << "Select an action: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			displayPlayerAttackMessage(player, enemy);
			player.attack(enemy);
			return;
		case 2:
			if(needHeal(player))	player.regenerate();
			else cout << "You don't need to heal!" << endl;
			break;
		case 3:
			if (flee(player))
			{
				displayFleeMessage(player);
				return;
			}
			break;
		case 4:
			if (needRepair(player))
			{			
				player.repairSelected();
				cout << "Repair sucessful!" << endl;
				return;
			}
			break;
		case 5:
			if (changeWeapon(player))
			{
				cout << "You have " << player.getWeapons().size() << " weapons." << endl;
				cout << "Current weapon: " << player.getSelectedWeapon()->getName() << endl;
				cout << "Select a weapon slot (1-" << player.getWeapons().size() << "): ";
				int index;
				cin >> index;
				index--;
				if (index < 0 || index >= player.getWeapons().size())
				{
					cout << "Invalid weapon slot!" << endl;
					break;
				}
				player.selectWeapon(index);
				cout << "Weapon changed!" << endl;
				return;
			}
			else
			{
				cout << "You can't change your weapons!" << endl;
				break;
			}
			cout << "You can't change weapons!" << endl;
			break;
		case 6:
			cout << "Player: " << player.getName() << " | Health: " << player.getHealth() << "/" << player.getMaxHp() << endl;
			cout << "Your level: " << player.getLevel() << " | Experience: " << player.getExperience() << "/" << player.getMaxExperience() << endl;
			cout << "Your weapon: " << player.getSelectedWeapon()->getName() << ", damage: " << player.getSelectedWeapon()->getDamage() << endl;
			cout << "Enemy: " << enemy.getName() << " | Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
			cout << "Enemy level: " << enemy.getLevel() << endl;
			cout << "Enemy weapon: " << enemy.getSelectedWeapon()->getName() << ", damage: " << enemy.getSelectedWeapon()->getDamage() << endl;
			break;
		default:
			cout << "Invalid choice!" << endl;
			cout << "Please select a valid action." << endl;
			break;
		}
	}
}

void Combat::enemyTurn(Character& enemy, Character& player)
{
	cout << "\nEnemy's turn!" << endl;
	displayEnemyAttackMessage(enemy, player);
	enemy.attack(player);
}

bool Combat::flee(const Character& player)
{
	string choice;
	while (true)
	{
		cout << "Are you sure you want to flee? (yes/no): ";
		cin >> choice;
		if (choice == "yes")
		{
			return true;
		}
		else if (choice == "no")
		{
			cout << "You chose to stay and fight!" << endl;
			return false;
		}
		else
		{
			cout << "Invalid choice! Please enter 'yes' or 'no'." << endl;
		}
	}
}

bool Combat::needHeal(Character& player)
{
	if (player.getHealth() == player.getMaxHp())
	{
		return false;
	}
	return true;
}

bool Combat::needRepair(Character& player)
{	
	Repairable* repairable = dynamic_cast<Repairable*>(player.getSelectedWeapon());
	if (repairable)
	{
		if (!repairable->isFullyRepaired())
		{
			return true;
		}
	}
	return false;
}


bool Combat::changeWeapon(Character& player)
{
	if(player.getWeapons().size()<=1)
		return false;
	return true;
}

void Combat::displayCombatInfo(const Character& player, const Character& enemy)
{
	cout << "Player: " << player.getName() << " | Health: " << player.getHealth() << "/" << player.getMaxHp() << endl;
	cout << "Enemy: " << enemy.getName() << " | Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
	cout << "-------------------------------------------" << endl;
}

void Combat::displayVictoryMessage(const Character& player)
{
	cout << player.getName() << " has defeated the enemy!" << endl;
	cout << "Fight Over!" << endl;
	cout << "You won!" << endl; 
	return;
}

void Combat::displayDefeatMessage(const Character& player)
{
	cout << player.getName() << " has been defeated!" << endl;
	cout << "Fight Over!" << endl;
	if(!player.isAlive())
		cout << "You died!" << endl;
	return;
}

void Combat::displayEnemyAttackMessage(const Character& enemy, const Character& player)
{
	cout << enemy.getName() << " attacks " << player.getName() << "!" << endl;
}

void Combat::displayPlayerAttackMessage(const Character& player, const Character& enemy)
{
	cout << player.getName() << " attacks " << enemy.getName() << "!" << endl;
}

void Combat::displayFleeMessage(const Character& player)
{
	cout << player.getName() << " has fled from the battle!" << endl;
	displayDefeatMessage(player);
}
