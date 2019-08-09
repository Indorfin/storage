#pragma once
#include "Fight.h"
class Prediction
{
private:
	
	string nameOne;
	string nameTwo;
	int winsOne;
	int winsTwo;
	int confidenceIndex;

public:
	
	Prediction();
	Prediction(Fight memberOf);
	~Prediction();

	string getNameOne();
	void setNameOne(string newName);
	string getNameTwo();
	void setNameTwo(string newName);
	int getWinsOne();
	void setWinsOne(int wins);
	int getWinsTwo();
	void setWinsTwo(int wins);
	int getConfidenceIndex();
	void setConfidenceIndex(int index);

	// void getNameInput();
	void getWinsInput();
	void getConfidenceInput();
};

