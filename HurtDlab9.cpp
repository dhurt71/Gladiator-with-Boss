//Author: Devon Hurt
//CPSC 121
//04/17/17

//Libraries
#include "BossFight.h"
#include <string>
#include <iostream>
using namespace std;

//Function that creates the party members and boss
void createGladiator(Gladiator & g)
{
	//Variables used to generate a random value to store in
	int health = 0;
	int evasion = 0;
	int crit = 0;

	//Prompt user for party and boss names
	cout << "Enter a character name: " << endl;
	cin >> g.name;

	health = rand() % 3 + 1;

	//Based off the number that the random generator gives, health is assigned
	if (health == 1)
	{
		g.maxHealth = 150;
	}
	if (health == 2)
	{
		g.maxHealth = 200;
	}
	if (health == 3)
	{
		g.maxHealth = 250;
	}
	g.curHealth = g.maxHealth;

	evasion = rand() % 5 + 1;

	//Based off the number that the random generator gives, evasion is assigned
	if (evasion == 1)
	{
		g.evasion = 5;
	}
	if (evasion == 2)
	{
		g.evasion = 7.5;
	}
	if (evasion == 3)
	{
		g.evasion = 10;
	}
	if (evasion == 4)
	{
		g.evasion = 12.5;
	}
	if (evasion == 5)
	{
		g.evasion = 15;
	}

	crit = rand() % 5 + 1;

	//Based off the number that the random generator gives, critical strike chance is assigned
	if (crit == 1)
	{
		g.critical = 5;
	}
	if (crit == 2)
	{
		g.critical = 7.5;
	}
	if (crit == 3)
	{
		g.critical = 1;
	}
	if (crit == 4)
	{
		g.critical = 12.5;
	}
	if (crit == 5)
	{
		g.critical = 15;
	}

	//Random generators assign the damage values between a minimum and maximum value
	g.dmgMin = rand() % 7 + 8;
	g.dmgRange = rand() % 7 + 16;
}

//Function that creates a boss based off of the createGladiator function
void BossFight::getBoss()
{
	Gladiator temp;
	createGladiator(temp);

	//Bosss is assigned 0 for crit and evasion, but has 6x more health and 3x more damage
	boss = temp;
	boss.critical = 0;
	boss.evasion = 0;
	boss.dmgMin *= 3;
	boss.dmgRange *= 3;
	boss.maxHealth *= 6;
	boss.curHealth = boss.maxHealth;
}

//Function that creates the gladiators and assigs them into an array
void BossFight::getParty()
{
	for (int i = 0; i < PSIZE; i++)
	{
		Gladiator temp;
		createGladiator(temp);
		party[i] = temp;
	}
}

//Function that creates the boss mechanic to damage all players for half damage
void BossFight::bossAttacksArea()
{
	int bossdamage;
	for (int i = 0; i < PSIZE; i++)
	{
		bossdamage = rand() % (boss.dmgRange - boss.dmgMin + 1) + boss.dmgMin / 2;
		party[i].curHealth = party[i].curHealth - bossdamage;
	}
	cout << boss.name << " has hit everyone for " << bossdamage << " damage!" << endl << endl;
}

//Function that allows the party and boss to continuously attack, on a turn basis, until one wins 
int BossFight::takeTurn()
{
	//Variables used to generate a random value to store in
	int usercrit;
	int userdamage;
	int bossdamage;
	int userevasion;
	int bossspecial;
	int bossdps;
	int bosstarget;

		//Displays the health of the party and boss each turn
		for (int i = 0; i < PSIZE; i++)
		{
			cout << party[i].name << ": " << party[i].curHealth << "/" << party[i].maxHealth << " ";
		}

		cout << endl;
		cout << "     " << boss.name << ": " << boss.curHealth << "/" << boss.maxHealth << endl;

		//Assigns the damage and crit values for every party member, then deals damage after determining of the party member crit
		for (int i = 0; i < PSIZE; i++)
		{
			userdamage = rand() % (party[i].dmgRange - party[i].dmgMin + 1) + party[i].dmgMin;
			usercrit = rand() % 100 + 1;

			if (usercrit < party[i].critical)
			{
				boss.curHealth = boss.curHealth - userdamage * 2;
				cout << party[i].name << " has CRITICALLY hit " << boss.name << " for " << userdamage * 2 << " damage!" << endl;
			}
			else
			{
				boss.curHealth = boss.curHealth - userdamage;
				cout << party[i].name << " has hit " << boss.name << " for " << userdamage << " damage!" << endl;
			}
		}

			//Variables used to generate a random value to store in
			userevasion = rand() % 100 + 1;
			bossdamage = rand() % (boss.dmgRange - boss.dmgMin + 1) + boss.dmgMin;
			bossspecial = rand() % 100 + 1;
			bossdps = rand() % 5 + 1;

			//Ensures the boss will attack players that are still alive
			bosstarget = rand() % 5;
			while (party[bosstarget].curHealth < 0)
			{
				bosstarget = rand() % 5 + 1;
			}

		//Chance for the boss to perform the boss mechanic or to attack a single party member
		if (bossspecial <= 30)
		{
			bossAttacksArea();
		}

		if (bossspecial >= 30)
		{
			//The random value will determine which party member to hit, then evasion is determined before the boss does damage
			if (bossdps == 1)
			{
				if (userevasion > party[0].evasion)
				{
					party[0].curHealth = party[0].curHealth - bossdamage;
					cout << boss.name << " did " << bossdamage << " damage to " << party[0].name << "!" << endl;
				}
				else
				{
					cout << party[0].name << " has dodged the attack!" << endl;
				}
			}

			else if (bossdps == 2)
			{
				if (userevasion > party[1].evasion)
				{
					party[1].curHealth = party[1].curHealth - bossdamage;
					cout << boss.name << " did " << bossdamage << " damage to " << party[1].name << "!" << endl;
				}

				else
				{
					cout << party[1].name << " has dodged the attack!" << endl;
				}

			}
	
			else if (bossdps == 3)
			{
				if (userevasion > party[2].evasion)
				{
					party[2].curHealth = party[2].curHealth - bossdamage;
					cout << boss.name << " did " << bossdamage << " damage to " << party[2].name << "!" << endl;
				}
				else
				{
					cout << party[2].name << " has dodged the attack!" << endl;
				}
			}

			else if (bossdps == 4)
			{
				if (userevasion > party[3].evasion)
				{
					party[3].curHealth = party[3].curHealth - bossdamage;
					cout << boss.name << " did " << bossdamage << " damage to " << party[3].name << "!" << endl;
				}
				else
				{
					cout << party[3].name << " has dodged the attack!" << endl;
				}
			}
			
			else if (bossdps == 5)
			{
				if (userevasion > party[4].evasion)
				{
					party[4].curHealth = party[4].curHealth - bossdamage;
					cout << boss.name << " did " << bossdamage << " damage to " << party[4].name << "!" << endl;
				}
				else
				{
					cout << party[4].name << " has dodged the attack!" << endl;
				}
			}
			cout << endl << endl;
			
		}

		//Determines if at least one member is alive, the fight continues
		int partyalive = 0;
		for (int i = 0; i < PSIZE; i++)
		{
			if (party[i].curHealth > 0)
			{
				partyalive = partyalive + 1;
			}
		}

		//If the party and boss are alive, the fight continues. If the party dies then the fight stops. If the party is alive, but the boss dies, then the fight stops.
		if (partyalive > 0)
		{
			if (boss.curHealth > 0)
			{
				return 2;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			return 0;
		}

}

//Function that displays statistics about the victories/losses
void BossFight::displayFightResults(bool partyWon)
{
	//Displays if the party won/loss
	if (partyWon == 0)
	{
		cout << "You are defeated after " << turnNum << " rounds! " << endl;
	}
	else
	{
		cout << "You are victorious after " << turnNum << " rounds!" << endl;
	}

	//Displays how many times the party is victorious out of how many times the party has fought the boss
	cout << "You've won " << fightsWon << " many times out of " << fightsStarted << endl;
}

//Function that initializes variables and creates the party/boss
BossFight::BossFight()
{
	 turnNum = 0, fightsStarted = 0, fightsWon = 0;

		getParty();
		getBoss();
}

//Function that calls the other functions to determine how the fight progresses
void BossFight::runFight()
{
	//Variables used to run loops again
	char userinput;
	int fightcontinue = 0;

		//Prompts the user to use the gladiators that were created
		cout << "Would you like to summon your existing gladiators? (Yes = y, No = n)" << endl;
		cin >> userinput;

		//If not, loop until the user is satisfied with the party members
		if (userinput == 'n')
		{
			getParty();
		}

		//After running the loop once, the party and the boss must have their health reset back to full
		for (int i = 0; i < PSIZE; i++)
		{
			party[i].curHealth = party[i].maxHealth;
		}

		boss.curHealth = boss.maxHealth;
		
		turnNum = 0;
		fightsStarted++;

		//Loop that continues the fight until the party or boss dies. The turnNum counts the number of turns until the loop stops
		//The fightsStarted counts the number of attempts have been started
		do
		{
			turnNum++;
			fightcontinue = takeTurn();
		} while (fightcontinue == 2);

		//If the party wins, takeTurn() will return 1 to exit the loop and will add to counter of how many fights have been won
		if (fightcontinue == 1)
		{
			fightsWon++;
		}

		//After the fight has been simulated, the statistics are displayed based on the fights done
		displayFightResults(fightcontinue);
}