//Eric May
//CPSC 121 Spring 2017
//Definition for our BossFight class
#pragma once
#include <string>

//Combat stats for a fighter
struct Gladiator {
	std::string name;
	int dmgMin, dmgRange,
		evasion, critical,
		maxHealth, curHealth;
};

const int PSIZE = 5;
//Allows for a fight between a team of five gladiators and a very powerful foe
class BossFight {
private:
	//Holds the party of gladiators that is banded together to fight the boss
	Gladiator party[PSIZE];
	//Holds the powerful boss that the party is fighting
	Gladiator boss;
	//Variables used for record keeping
	int turnNum, fightsStarted, fightsWon;
	//Will fill the party with gladiators, this function can call/reuse the createGladiator function.
	void getParty();
	//Will generate a boss for the party to fight. Has no crit or evasion, but 3* damage min and range, and 6* health
	void getBoss();
	//Tells the user who won, after how many turns, and the current record for the session
	void displayFightResults(bool partyWon);
	//One turn occurs, where each party member attacks the boss, then the boss attacks the party.
	//Returned value indicates status of fight (continue, party win, party loss)
	//Boss will randomly choose between attacking a single (randomly chosen) party member for full damage, or
	//attacking the full party for half damage.
	int takeTurn();
	//Handles dealing damage to the entire party
	void bossAttacksArea();
public:
	//Responsible for generating the party and the boss, should initialize the other
	//private variables as well
	BossFight();
	//User calls this when they want to run a fight. It will ask them if they want to use
	//the same party, or get a new one.
	void runFight();
};

//Functions that don't need to be part of our class, but may be useful:
//Generates stats and reads input to form a gladiator
//void generateFighter(Gladiator & g)
//off attacks def, removing HP after calculating damage + modifiers
//void attack(Gladiator off, Gladiator& def)