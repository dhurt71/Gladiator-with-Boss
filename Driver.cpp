//Eric May
//CPSC 121 Spring 2017
//Driver program for our BossFight class
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "BossFight.h"
using namespace std;

int main()
{
	srand(time(NULL));
	BossFight b;
	char doAgain = 'y';
	while (toupper(doAgain) == 'Y') {
		b.runFight();
		cout << "Go again? y/n ";
		cin >> doAgain;
	}
}