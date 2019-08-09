/* 

PREDICTION CLASS
	Knows name of fighters
		Names are passed from one Prediction to another by constructor
	Holds anticipated outcome
		fighterOneWins, fighterTwoWins
	Holds confidence index
		the multiplier effect should be controlled by numbers in the header to avoid "magic numbers"
			roughly 5-10% variance per point below perfect
		Details of confidence index-point system
			5
				Familiar with all aspects of both fighters' game at this level of competition AND no recent absences, injuries or changes on either side
			4
				Familiar with any relevant aspects of both fighters game at similar level of competition AND no significant absences, injuries or changes on either side
			3
				Familiar with figher's usual weapons, but they may be fighting against a different match-up stylistically or talent-wise OR 
				have had a significant absence, injury, or changes in coaches or style
			2
				Not familiar with a fighter OR someone has had a significant absence OR has never fought this style or level of talent 
				OR someone's health status is uncertain OR a fighter's recent fights have been inconsistent with their past performance
			1 
				Multiple aspects of 2 score, or an aspect applies to each fighter
				

COMBINING PREDICTIONS
	Weighted based on confidence index

FIGHT CLASS
	Varibles
		Total confidence index
		Total score for each fighter

complexPick
	Assign a 0 - 3 for each podcaster
		0 - Can't pick
		1 - Doesn't want to pick
		2 - Normal pick
		3 - Definite pick
	Enter as 1 - 7
		1 - 3 for second fighter
		2 - 2 for second fighter
		3 - 1 for second fighter
		4 - 0
		5 - 1 for first fighter
		6 - 2 for first fighter
		7 - 3 for first fighter
			Each prediction adds 6 to totalPicks, and the entered number - 1 to pickedOne
	Program will take predictions until an affirmative is entered

	TO DO LIST:
	Design qualatative outside picks system


WEIGHTING TEST
	Things that need to be split
		WEIGHT
			Could instead use a loop that increases by .1
				This code would be far more portable
				Easier to write
				ScoreOne and ScoreTwo would need to be replaced by a vector
*/



#include "stdafx.h"
#include "Prediction.h"



int main()
{
	
	string fileName;
	cout << endl << "Are you using the default output file?" << endl;
	string usingDefaultFile;
	cin >> usingDefaultFile;
	if (!(usingDefaultFile == "yes" || usingDefaultFile == "y" || usingDefaultFile == "+"))
	{
		cout << "\n\nWhat would you like to name the new file?" << endl;
		string temp;
		cin >> temp;
		fileName = "C:/Users/Zac/Desktop/";
		fileName.append(temp);
		fileName.append(".dat");
	}
	else
	{
		fileName = "LongFormOdds.dat";
	}

	ofstream outputFile(fileName, ios::app);
	string input;
	do
	{
		Fight fight(outputFile);
		cout << endl << "Do you want to enter another fight?" << endl;
		cin >> input;
	} while (input == "yes" || input == "y" || input == "+");


	system("pause");
    return 0;
}

