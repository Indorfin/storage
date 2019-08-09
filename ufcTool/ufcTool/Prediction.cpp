#include "stdafx.h"
#include "Prediction.h"


Prediction::Prediction()
{
	
}

Prediction::Prediction(Fight memberOf) : nameOne(memberOf.getNameOne()), nameTwo(memberOf.getNameTwo())
{
	getWinsInput();
	getConfidenceInput();
}

string Prediction::getNameOne()
{
	return nameOne;
}

void Prediction::setNameOne(string newName)
{
	nameOne = newName;
}

string Prediction::getNameTwo()
{
	return nameTwo;
}

void Prediction::setNameTwo(string newName)
{
	nameTwo = newName;
}

int Prediction::getWinsOne()
{
	return winsOne;
}

void Prediction::setWinsOne(int wins)
{
	winsOne = wins;
}

int Prediction::getWinsTwo()
{
	return winsTwo;
}

void Prediction::setWinsTwo(int wins)
{
	winsTwo = wins;
}

int Prediction::getConfidenceIndex()
{
	return confidenceIndex;
}

void Prediction::setConfidenceIndex(int index)
{
	confidenceIndex = index;
}
/*
void Prediction::getNameInput()
{
	string name;
	cout << endl << "Enter first fighter's name" << endl;
	do
	{
		getline(cin, name);
	} while (name.empty());
	setNameOne(name);

	cout << endl << endl << "Enter second fighter's name" << endl;
	do
	{
		getline(cin, name);
	} while (name.empty());
	setNameTwo(name);
}
*/
void Prediction::getWinsInput()
{
	cout.unsetf(std::ios::showpos);
	cout << endl << endl << "How many fights does " << getNameOne() << " WIN AGAINST " << getNameTwo() << "? (out of " << NUMBER_OF_FIGHTS << ")" << endl;
	int input;
	do
	{
		cin >> input;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (input < 0 && input > NUMBER_OF_FIGHTS);
	setWinsOne(input);
	setWinsTwo(NUMBER_OF_FIGHTS - input);
}

void Prediction::getConfidenceInput()
{
	cout << endl << endl << "How thoroughly do you know BOTH fighters?" << endl
		/*<< endl
		<< "\n5: \nFamiliar with all aspects of both fighters' game at this level of competition \nAND no recent absences, injuries or changes on either side" << endl
		<< "\n4: \nFamiliar with any relevant aspects of both fighters game at similar level of competition \nAND no significant absences, injuries or changes on either side" << endl
		<< "\n3: \nFamiliar with figher's usual weapons, but they may be fighting against a different match-up stylistically or talent-wise \nOR have had a significant absence, injury, or changes in coaches or style \nOR is coming off of an abnormal performance" << endl
		<< "\n2: \nNot familiar with a fighter \nOR someone has had a significant absence \nOR has never fought this style or level of talent \nOR someone's health status is uncertain \nOR a fighter's recent fights have been inconsistent with their past performance" << endl
		<< "\n1: \nMultiple aspects of a 2 score, or an aspect applies to each fighter" << endl*/;
	int input;
	do
	{
		cin >> input;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (input < 0);
	setConfidenceIndex(input);
}


Prediction::~Prediction()
{
}
