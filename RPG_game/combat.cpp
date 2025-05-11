#include "combat.h"

using namespace std;

void Combat::start(Character& player)
{
	srand(static_cast<unsigned>(time(0))); // Seed a random generator
	while (true)
	{
		cout << endl;
		displayMenu();
		int choice;
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			wander(player);
			break;
		case 2:
			displayInventory(player);
			break;
		case 3:
			displayCharacterInfo(player);
			break;
		case 4:
			displayWeaponInfo(player);
			break;
		case 5:
			if (quitGame())
			{
				cout << "Exiting the game..." << endl;
				return;
			}
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
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
		string name = "Weapon";
		if (dynamic_cast<Warrior*>(&player))
		{
			int weaponName = rand() % 3;
			switch (weaponName)
			{
			case 0:
				name = "Excalibur Sword";
				break;
			case 1:
				name = "Stormbringer Axe";
				break;
			case 2:
				name = "Mighty Spear";
				break;
			default:
				name = "Unknown Weapon";
				break;
			}
			name += " (Level " + to_string(player.getLevel()) + ")";
			newWeapon = new Melee(name, 20 + (player.getLevel() - 1) * 10, 6 + player.getLevel() - 1);
		}
		else if (dynamic_cast<Wizard*>(&player))
		{
			int weaponName = rand() % 3;
			switch (weaponName)
			{
			case 0:
				name = "Fire Staff";
				break;
			case 1:
				name = "Ice Wand";
				break;
			case 2:
				name = "Lightning Rod";
				break;
			default:
				name = "Unknown Weapon";
				break;
			}
			name += " (Level " + to_string(player.getLevel()) + ")";
			newWeapon = new Magic(name, 20 + (player.getLevel() - 1) * 10, 20 + (player.getLevel() - 1) * 10);
		}
		else if (dynamic_cast<Archer*>(&player))
		{
			int weaponName = rand() % 3;
			switch (weaponName)
			{
			case 0:
				name = "Longbow of the Ancients";
				break;
			case 1:
				name = "Crossbow of Shadows";
				break;
			case 2:
				name = "Swift Bow";
				break;
			default:
				name = "Unknown Weapon";
				break;
			}
			name += " (Level " + to_string(player.getLevel()) + ")";
			newWeapon = new Ranged(name, 20 + (player.getLevel() - 1) * 10, 4 + player.getLevel() - 1);
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

		if (!player.isAlive())
		{
			displayDefeatMessage(player);
			break;
		}

		if (!enemy.isAlive())
		{
			player.gainXp(enemy.getMaxExperience()*0.5);
			player.changeHealth(player.getMaxHp());
			displayVictoryMessage(player);
			break;
		}

		playerTurn(player, enemy);
		if (player.getFleeing())
		{
			player.setFleeing(false);
			break;
		}
		if (enemy.isAlive())
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
				player.setFleeing(true);
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
				break;
			}
			else
			{
				cout << "You can't change your weapons!" << endl;
				break;
			}
			cout << "You can't change weapons!" << endl;
			break;
		case 6:
			displayCharacterInfo(player);
			displayWeaponInfo(player);
			displayEnemyInfo(enemy);
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

void Combat::displayMenu()
{
	cout << "MENU" << endl;
	cout << "1. Wander in the wilderness" << endl;
	cout << "2. Check your inventory" << endl;
	cout << "3. Check your character info" << endl;
	cout << "4. Check your weapon info" << endl;
	cout << "5. Quit game" << endl;
	cout << "Choice: ";
}

void Combat::displayInventory(const Character& player)
{
	cout << "Your inventory:" << endl;
	player.displayWeapons();
}

void Combat::displayCharacterInfo(Character& player)
{
	cout << "Your character:" << endl;
	cout << "Name: " << player.getName() << endl;
	cout << "Health: " << player.getHealth() << "/" << player.getMaxHp() << endl;
	cout << "Level: " << player.getLevel() << endl;
	cout << "Experience: " << player.getExperience() << "/" << player.getMaxExperience() << endl;
	{
		Wizard* wizard = dynamic_cast<Wizard*>(&player);
		if (wizard)
		{
			cout << "Class: wizard" << endl;
			cout << "Mana: " << wizard->getMana() << "/" << wizard->getMaxMana() << endl;
		}
	}
	{
		Warrior* warrior = dynamic_cast<Warrior*>(&player);
		if (warrior)
		{
			cout << "Class: warrior" << endl;
			cout << "Shield: " << warrior->getShield() << "/" << warrior->getMaxShield() << endl;
		}
	}
	{
		Archer* archer = dynamic_cast<Archer*>(&player);
		if (archer)
		{
			cout << "Class: archer" << endl;
		}
	}
	cout << "Current weapon: " << player.getSelectedWeapon()->getName() << endl;
}

void Combat::displayWeaponInfo(const Character& player)
{
	cout << "Your current weapon:" << endl;
	cout << "Name: " << player.getSelectedWeapon()->getName() << endl;
	cout << "Damage: " << player.getSelectedWeapon()->getDamage() << endl;
	{
		Melee* melee = dynamic_cast<Melee*>(player.getSelectedWeapon());
		if (melee)
		{
			cout << "Durability: " << melee->getDurability() << "/" << melee->getMaxDurability() << endl;
		}
	}
	{
		Magic* magic = dynamic_cast<Magic*>(player.getSelectedWeapon());
		if (magic)
		{
			cout << "Mana cost: " << magic->getManaCost() << endl;
		}
	}
	{
		Ranged* ranged = dynamic_cast<Ranged*>(player.getSelectedWeapon());
		if (ranged)
		{
			cout << "Ammo: " << ranged->getAmmo() << "/" << ranged->getMaxAmmo() << endl;
		}
	}
}

void Combat::displayEnemyInfo(Character& enemy)
{
	cout << "Enemy info:" << endl;
	cout << "Name: " << enemy.getName() << endl;
	cout << "Level: " << enemy.getLevel() << endl;
	cout << "Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << endl;
	{
		Wizard* wizard = dynamic_cast<Wizard*>(&enemy);
		if (wizard)
		{
			cout << "Mana: " << wizard->getMana() << "/" << wizard->getMaxMana() << endl;
		}
	}
	{
		Warrior* warrior = dynamic_cast<Warrior*>(&enemy);
		if (warrior)
		{
			cout << "Shield: " << warrior->getShield() << "/" << warrior->getMaxShield() << endl;
		}
	}
	cout << "Weapon: " << enemy.getSelectedWeapon()->getName() << endl;
	{
		Melee* melee = dynamic_cast<Melee*>(enemy.getSelectedWeapon());
		if (melee)
		{
			cout << "Durability: " << melee->getDurability() << "/" << melee->getMaxDurability() << endl;
		}
	}
	{
		Magic* magic = dynamic_cast<Magic*>(enemy.getSelectedWeapon());
		if (magic)
		{
			cout << "Mana cost: " << magic->getManaCost() << endl;
		}
	}
	{
		Ranged* ranged = dynamic_cast<Ranged*>(enemy.getSelectedWeapon());
		if (ranged)
		{
			cout << "Ammo: " << ranged->getAmmo() << "/" << ranged->getMaxAmmo() << endl;
		}
	}

}

void Combat::wander(Character& player)
{
	while (true)
	{
		cout << endl;
		cout << "You are wandering in the wilderness..." << endl;
		// Generate a random enemy whose level is equal to or below the player's level
		Character* enemy = generateRandomEnemy(player.getLevel());
		cout << endl;
		cout << "-------------------------------------------" << endl;
		cout << "An evil " << enemy->getName() << " (Level " << enemy->getLevel() << ") has appeared!" << endl;

		// Pre-combat menu
		cout << "1. Watch enemy" << endl;
		cout << "2. Quit game" << endl;
		cout << "Choice: ";
		int choice;
		std::cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			cout << "You chose to watch the enemy!" << endl;
			displayEnemyInfo(*enemy);
			watchEnemy(player, enemy);
			break;
		case 2:
			if(quitGame())
			{
				cout << "Exiting the game..." << endl;
				delete enemy;
				return;
			}
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			continue;
		}

		// Check for level-up rewards
		if (player.checkLevelUp())
		{
			manageLevelUpRewards(player);
			player.setReward(true);
		}

		// Check if the player wants to continue playing

	}
}

void Combat::watchEnemy(Character& player, Character* enemy)
{
	while (true)
	{
		cout << "1. Fight the enemy" << endl;
		cout << "2. Go away" << endl;
		cout << "3. Quit game" << endl;
		cout << "Choice: ";
		int choice;
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			cout << "You chose to fight the enemy!" << endl;
			fight(player, *enemy);
			if (!player.isAlive())
			{
				cout << "Game Over! You have been defeated." << endl;
				delete enemy;
				return;
			}
			break;
		case 2:
			cout << "You chose wander around a little bit more." << endl;
			delete enemy;
			return;
		case 3:
			if (quitGame())
			{
				cout << "Exiting the game..." << endl;
				delete enemy;
				exit(0);
			}
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
			continue;
		}
	}
}

bool Combat::quitGame()
{
	cout << "Are you sure you want to quit? (yes/no): ";
	while (true)
	{
		string response;
		cin >> response;
		if (response == "no")
		{
			cout << "Continuing your adventure..." << endl;
			return false;
		}
		else if (response == "yes")
		{
			cout << "Thanks for playing!" << endl;
			return true;
		}
		else
		{
			cout << "Please answer 'yes' or 'no'!" << endl;
			continue;
		}
	}
}

void Combat::displayFleeMessage(const Character& player)
{
	cout << player.getName() << " has fled from the battle!" << endl;
	displayDefeatMessage(player);
}
