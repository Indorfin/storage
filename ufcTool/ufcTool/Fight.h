#pragma once

class Prediction;
class Fight
{
public:
	Fight(ofstream &);
	~Fight();

private:
	string nameOne;
	string nameTwo;
	int okayScoreOne;
	int scoreOne;
	int safeScoreOne;
	int outsideScoreOne;
	int outsideSafeScoreOne;
	int mixedScoreOne;
	int mixedSafeScoreOne;
	int okayScoreTwo;
	int scoreTwo;
	int safeScoreTwo;
	int outsideScoreTwo;
	int outsideSafeScoreTwo;
	int mixedScoreTwo;
	int mixedSafeScoreTwo;
	int alternateScoreOne;
	int alternateScoreTwo;
	int alternateSafeScoreOne;
	int alternateSafeScoreTwo;
	int trueScoreOne;
	int trueScoreTwo;
	int trueScoreOneExtra;
	int trueScoreTwoExtra;
	int picksAgainstOne;
	int picksAgainstTwo;
	int totalIndex;
	int numberOfPicks;
	int confidenceIndex;
	int TESTindex;
	double weightIndex;
	double mixedIndex;
	double pickedFirst;
	int totalPicks;
	vector<string> affirmative;
	vector<double> TESTscoreOne;
	vector<double> TESTscoreTwo;
	vector<double> TESTindexes;
	ofstream &longFile;

public:
	void addScore(Prediction &current);
	void printOdds();
	int calculateOkayScore(double wins, int confidenceIndex);
	int calculateScore(double wins, int confidenceIndex);
	int calculateSafeScore(double wins, int confidenceIndex);
	int calculateAlternateScore(int wins);
	int calculateAlternateSafeScore(int wins);
	int calculateTrueScore(int wins);
	double calculateMixedScore(int score, int index);
	void addFightPick();
	void addOutsidePicks();
	int mainOutsideAlgorithm(double total, double wins);
	int secondOutsideAlgorithm(double total, double wins);
	int thirdOutsideAlgorithm(double total, double wins);
	void saveToFile();
	void pickBets();

	string getNameOne();
	void setNameOne(string name);
	string getNameTwo();
	void setNameTwo(string name);
	int getScoreOne();
	void setScoreOne(int score);
	int getScoreTwo();
	void setScoreTwo(int score);

	void getNameInput();
};

