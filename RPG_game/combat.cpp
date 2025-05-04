#include "combat.h"

void Combat::start(Character& player, Character& enemy)
{
	std::cout << "An evil " << enemy.getName() << " appears!" << std::endl;
	std::cout << "Fight!" << std::endl;
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
			displayVictoryMessage(player);
			break;
		}
		playerTurn(player, enemy);
		if (enemy.getHealth() <= 0)
		{
			displayVictoryMessage(player);
			break;
		}
		enemyTurn(enemy, player);
		if (player.getHealth() <= 0)
		{
			displayDefeatMessage(player);
			break;
		}
	}
}

void Combat::playerTurn(Character& player, Character& enemy)
{
	int choice;
	while (true)
	{
		std::cout << "Your turn!" << std::endl;
		std::cout << "1. Attack" << std::endl;
		std::cout << "2. Heal" << std::endl;
		std::cout << "3. Flee" << std::endl;
		std::cout << "4. Repair" << std::endl;
		std::cout << "5. Change weapon" << std::endl;
		std::cout << "6. Display Info" << std::endl;
		std::cout << "Select an action: ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			displayPlayerAttackMessage(player, enemy);
			player.attack(enemy);
			break;
		case 2:
			if(needHeal(player))	player.regenerate();
			else std::cout << "You don't need to heal!" << std::endl;
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
				player.getInventory().repairSelected();
				std::cout << "Repair sucessful!" << std::endl;
				return;
			}
			break;
		case 5:
			if(changeWeapon(player))
			{
				player.getInventory().selectWeapon(player.getInventory().getSelectedIndex());
				std::cout << "Weapon changed!" << std::endl;
				return;
			}
			std::cout << "You can't change weapons!" << std::endl;
			break;
		case 6:
			std::cout << "Player: " << player.getName() << " | Health: " << player.getHealth() << "/" << player.getMaxHp() << std::endl;
			std::cout << "Enemy: " << enemy.getName() << " | Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << std::endl;
			break;
		default:
			std::cout << "Invalid choice!" << std::endl;
			std::cout << "Please select a valid action." << std::endl;
			break;
		}
	}
}

void Combat::enemyTurn(Character& enemy, Character& player)
{
	std::cout << "Enemy's turn!" << std::endl;
	displayEnemyAttackMessage(enemy, player);
	enemy.attack(player);
}

bool Combat::flee(const Character& player)
{
	std::string choice;
	while (true)
	{
		std::cout << "Are you sure you want to flee? (yes/no): ";
		std::cin >> choice;
		if (choice == "yes" || choice == "Yes")
		{
			return true;
		}
		else if (choice == "no" || choice == "No")
		{
			std::cout << "You chose to stay and fight!" << std::endl;
			return false;
		}
		else
		{
			std::cout << "Invalid choice! Please enter 'yes' or 'no'." << std::endl;
		}
	}
}

bool Combat::needHeal(Character& player)
{
	if (player.getHealth() == player.getMaxHp())
	{
		return true;
	}
	return false;
}

bool Combat::needRepair(Character& player)
{	

	return player.getInventory().getSelectedWeapon();
}

bool Combat::changeWeapon(Character& player)
{
	if(player.getInventory().getWeapons().size()<=1)
		return false;
	return true;
}

void Combat::displayCombatInfo(const Character& player, const Character& enemy)
{
	std::cout << "Player: " << player.getName() << " | Health: " << player.getHealth() << "/" << player.getMaxHp() << std::endl;
	std::cout << "Enemy: " << enemy.getName() << " | Health: " << enemy.getHealth() << "/" << enemy.getMaxHp() << std::endl;
	std::cout << "-------------------------------------------" << std::endl;
}

void Combat::displayVictoryMessage(const Character& player)
{
	std::cout << player.getName() << " has defeated the enemy!" << std::endl;
	std::cout << "Fight Over!" << std::endl;
	std::cout << "You won!" << std::endl;
	std::cout << "Press any key to exit." << std::endl;
	std::cin.get();
	exit(0);
}

void Combat::displayDefeatMessage(const Character& player)
{
	std::cout << player.getName() << " has been defeated!" << std::endl;
	std::cout << "Fight Over!" << std::endl;
	std::cout << "You died!" << std::endl;
	std::cout << "Press any key to exit." << std::endl;
	std::cin.get();
	exit(0);
}

void Combat::displayEnemyAttackMessage(const Character& enemy, const Character& player)
{
	std::cout << enemy.getName() << " attacks " << player.getName() << "!" << std::endl;
}

void Combat::displayPlayerAttackMessage(const Character& player, const Character& enemy)
{
	std::cout << player.getName() << " attacks " << enemy.getName() << "!" << std::endl;
}

void Combat::displayFleeMessage(const Character& player)
{
	std::cout << player.getName() << " has fled from the battle!" << std::endl;
	displayDefeatMessage(player);
}
