#include "stdafx.h"
#include "Fight.h"
#include "Prediction.h"

// Entering a + when asked how many fights each wins will assign the + to tempScore, or leave it uninitialized, creating an error
// 


Fight::Fight(ofstream &c_longFile) : okayScoreOne(0), okayScoreTwo(0), scoreOne(0), scoreTwo(0), safeScoreOne(0), safeScoreTwo(0),
outsideScoreOne(0), outsideScoreTwo(0), outsideSafeScoreOne(0), outsideSafeScoreTwo(0), mixedScoreOne(0), mixedScoreTwo(0),
mixedSafeScoreOne(0), mixedSafeScoreTwo(0), alternateScoreOne(0), alternateScoreTwo(0), alternateSafeScoreOne(0), alternateSafeScoreTwo(0),
trueScoreOne(0), trueScoreTwo(0), trueScoreOneExtra(0), trueScoreTwoExtra(0), picksAgainstOne(0), picksAgainstTwo(0), totalIndex(0), weightIndex(0), mixedIndex(0),
confidenceIndex(0), numberOfPicks(0), totalPicks(0), pickedFirst(0), longFile(c_longFile), TESTindex(0)
{
	TESTscoreOne.assign(11, 0);
	TESTscoreTwo.assign(11, 0);
	TESTindexes.assign(11, 0);
	affirmative.push_back("y");
	affirmative.push_back("Y");
	affirmative.push_back("yes");
	affirmative.push_back("Yes");
	affirmative.push_back("YES");
	affirmative.push_back("+");
	affirmative.push_back("yep");
	affirmative.push_back("Yep");
	affirmative.push_back("YEP");
	affirmative.push_back("ye");
	affirmative.push_back("Ye");
	affirmative.push_back("YE");
	affirmative.push_back("ya");
	affirmative.push_back("Ya");
	affirmative.push_back("YA");
	affirmative.push_back("es");
	affirmative.push_back("ES");
	affirmative.push_back("yeah");
	affirmative.push_back("Yeah");
	affirmative.push_back("YEAH");
	affirmative.push_back("ja");
	affirmative.push_back("Ja");
	affirmative.push_back("JA");
	affirmative.push_back("si");
	affirmative.push_back("Si");
	affirmative.push_back("SI");

	getNameInput();
	string input;
	cout << endl << "Do you want to enter a polled prediction?" << endl;
	cin >> input;
	if (find(affirmative.begin(), affirmative.end(), input) != affirmative.end())
	{
		cin.sync();
		do
		{
			Prediction current(*this);
			addScore(current);
			//int tempOne = okayScoreOne / totalIndex;
			//int tempTwo = okayScoreTwo / totalIndex;
			//tempOne > 0 ? tempOne += 100 : tempOne -= 100;
			//tempTwo > 0 ? tempTwo += 100 : tempTwo -= 100;


			cout << endl << "Do you want to add another prediction?" << endl;
			cin >> input;
		} while (find(affirmative.begin(), affirmative.end(), input) != affirmative.end());
		printOdds();
		mixedScoreOne = scoreOne;
		mixedScoreTwo = scoreTwo;
		mixedSafeScoreOne = safeScoreOne;
		mixedSafeScoreTwo = safeScoreTwo;
	}
	addOutsidePicks();

	cout << endl << "Do you want to save these odds?" << endl;
	cin >> input;
	if (find(affirmative.begin(), affirmative.end(), input) != affirmative.end()) saveToFile();
}


Fight::~Fight()
{
}

void Fight::getNameInput()
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

void Fight::addScore(Prediction &current)
{
	int returnedTrueScore = 0;
	int index = current.getConfidenceIndex();
	TESTindex += index;
	confidenceIndex += index;
	double weight = 1 + ((index - 1) * WEIGHT);
	//okayScoreOne += weight * calculateOkayScore(current.getWinsOne(), index);
	//okayScoreTwo += weight * calculateOkayScore(current.getWinsTwo(), index);
	scoreOne += weight * calculateScore(current.getWinsOne(), index);
	scoreTwo += weight * calculateScore(current.getWinsTwo(), index);
	// From here to the bottom of the brackets is for the weight test
	int TESTscoreOneCopy = calculateSafeScore(current.getWinsOne(), index);
	int TESTscoreTwoCopy = calculateSafeScore(current.getWinsTwo(), index);
	{
		for (int i = 0; i <= 10; ++i)
		{
			double TESTweight = i / 10.0;
			TESTindexes[i] += (1 + (TESTweight * (index - 1)));
			int TESTtempScoreOne = TESTscoreOne[i];
			int TESTtempScoreTwo = TESTscoreTwo[i];
			TESTtempScoreOne += TESTscoreOneCopy * (1 + (TESTweight * (index - 1)));
			TESTtempScoreTwo += TESTscoreTwoCopy * (1 + (TESTweight * (index - 1)));
			TESTscoreOne[i] = TESTtempScoreOne;
			TESTscoreTwo[i] = TESTtempScoreTwo;
			

		}
	}
	(scoreOne > 0) ? scoreOne += scoreOne * SCORE_MODIFIER : scoreOne -= scoreOne * SCORE_MODIFIER;
	(scoreTwo > 0) ? scoreTwo += scoreTwo * SCORE_MODIFIER : scoreTwo -= scoreTwo * SCORE_MODIFIER;
	safeScoreOne += weight * calculateSafeScore(current.getWinsOne(), index);
	safeScoreTwo += weight * calculateSafeScore(current.getWinsTwo(), index);
	alternateScoreOne += weight * calculateAlternateScore(current.getWinsOne());
	alternateScoreTwo += weight * calculateAlternateScore(current.getWinsTwo());
	alternateSafeScoreOne += weight * calculateAlternateSafeScore(current.getWinsOne());
	alternateSafeScoreTwo += weight * calculateAlternateSafeScore(current.getWinsTwo());

	returnedTrueScore = calculateTrueScore(current.getWinsOne());
	trueScoreOne += returnedTrueScore;
	if (current.getWinsOne() < 5)
	{
		++picksAgainstOne;
		returnedTrueScore *= 2;
	}
	trueScoreOneExtra += returnedTrueScore;

	returnedTrueScore = calculateTrueScore(current.getWinsTwo());
	trueScoreTwo += returnedTrueScore;
	if (current.getWinsTwo() < 5)
	{
		++picksAgainstTwo;
		returnedTrueScore *= 2;
	}
	trueScoreTwoExtra += returnedTrueScore;

	//trueScoreOne += calculateTrueScore(current.getWinsOne());
	//trueScoreTwo += calculateTrueScore(current.getWinsTwo());
	totalIndex += index;
	mixedIndex += weight;
	weightIndex += weight;
	++numberOfPicks;
}

void Fight::printOdds()
{
	cout.unsetf(std::ios::showpos);
	cout << "\tConfidence: " << confidenceIndex << endl << "\tPicks: " << numberOfPicks << endl << nameOne << ":" << endl;
	cout.setf(std::ios::showpos);

	if (scoreOne != 0)
	{
		cout << "Good Bet: " << llround(scoreOne / weightIndex) << endl;
	}

	if (safeScoreOne != 0)
	{
		cout << "Safe Bet: " << llround(safeScoreOne / weightIndex) << endl;
	}

	if (outsideScoreOne != 0)
	{
		cout << "Outside Score: " << llround(outsideScoreOne) << endl;
	}
	if (outsideSafeScoreOne != 0)
	{
		cout << "Outside Safe Score: " << llround(outsideSafeScoreOne) << endl;
	}
	if (mixedScoreOne != 0)
	{
		cout << "Mixed Score: " << llround(mixedScoreOne / mixedIndex) << endl;
	}
	if (mixedSafeScoreOne != 0)
	{
		cout << "Mixed Safe Score: " << llround(mixedSafeScoreOne / mixedIndex) << endl;
	}
	
	if (alternateScoreOne != 0)
	{
		cout << "New Algorithm: " << llround(alternateScoreOne / weightIndex) << endl;
	}

	if (alternateSafeScoreOne != 0)
	{
		cout << "New/Safe: " << llround(alternateSafeScoreOne / weightIndex) << endl;
	}



	cout << endl << endl << nameTwo << ":" << endl;
	if (scoreTwo != 0)
	{
		cout << "Good Bet: " << llround(scoreTwo / weightIndex) << endl;
	}
	if (safeScoreTwo != 0)
	{
		cout << "Safe Bet: " << llround(safeScoreTwo / weightIndex) << endl;
	}
	if (outsideScoreTwo != 0)
	{
		cout << "Outside Score: " << llround(outsideScoreTwo) << endl;
	}
	if (outsideSafeScoreTwo != 0)
	{
		cout << "Outside Safe Score: " << llround(outsideSafeScoreTwo) << endl;
	}
	if (mixedScoreTwo != 0)
	{
		cout << "Mixed Score: " << llround(mixedScoreTwo / mixedIndex) << endl;
	}
	if (mixedSafeScoreTwo != 0)
	{
		cout << "Mixed Safe Score: " << llround(mixedSafeScoreTwo / mixedIndex) << endl;
	}

	if (alternateScoreTwo != 0)
	{
		cout << "New Algorithm: " << llround(alternateScoreTwo / weightIndex) << endl;
	}

	if (alternateSafeScoreTwo != 0)
	{
		cout << "New/Safe: " << llround(alternateSafeScoreTwo / weightIndex) << endl;
	}

}

/*int Fight::calculateOkayScore(int wins, int confidenceIndex)
{
	double tempScore;
	double losses = NUMBER_OF_FIGHTS - wins;

	if (wins == 0)
	{
		tempScore = 1500;
	}
	else if (wins == 10)
	{
		tempScore = -1500;
	}
	else if (wins >= 5)
		tempScore = (wins / (NUMBER_OF_FIGHTS - wins) * -100);
	else
		tempScore = 100 / (wins / losses);

	

	return tempScore;
}*/

int Fight::calculateScore(double wins, int confidenceIndex)
{
	double tempScore;
	double losses = NUMBER_OF_FIGHTS - wins;
	// double modifier = (MAX_CONFIDENCE_INDEX - confidenceIndex) * CONFIDENCE_INDEX_MODIFIER;
	if (wins == 0)
	{
		tempScore = 1800;
	}
	else if (wins == NUMBER_OF_FIGHTS)
	{
		tempScore = -1800;
	}
	else if (wins >= NUMBER_OF_FIGHTS / 2)
		tempScore = (wins / (NUMBER_OF_FIGHTS - wins) * -100);
	else
	tempScore = 100 / (wins / losses);
	/*
	if (tempScore > 0)
		tempScore += tempScore * modifier;
	else
		tempScore -= tempScore * modifier;
		*/
	return tempScore;
}

int Fight::calculateSafeScore(double wins, int confidenceIndex)
{
	double tempScore;
	double losses = NUMBER_OF_FIGHTS - wins;
	// double modifier = (MAX_CONFIDENCE_INDEX - confidenceIndex) * CONFIDENCE_INDEX_MODIFIER;
	if (wins == 0)
	{
		tempScore = 3600;
	}
	else if (wins == 10)
	{
		tempScore = -900;
	}
	else if (wins >= 5)
		tempScore = (wins / (NUMBER_OF_FIGHTS - wins) * -50);
	else
		tempScore = 200 / (wins / losses);

	/*if (tempScore > 0)
		tempScore += tempScore * modifier;
	else
		tempScore -= tempScore * modifier; */

	return tempScore;
}

int Fight::calculateAlternateScore(int wins)
{
	int tempScore;
	
	switch (wins)
	{
	case 0: tempScore = 750;
		break;
	case 1: tempScore = 600;
		break;
	case 2: tempScore = 450;
		break;
	case 3: tempScore = 300;
		break;
	case 4: tempScore = 150;
		break;
	case 5: tempScore = 0;
		break;
	case 6: tempScore = -150;
		break;
	case 7: tempScore = -300;
		break;
	case 8: tempScore = -450;
		break;
	case 9: tempScore = -600;
		break;
	case 10: tempScore = -750;
		break;
	
	}
	return tempScore;
}

int Fight::calculateAlternateSafeScore(int wins)
{
	int tempScore;

	switch (wins)
	{
	case 0: tempScore = 1000;
		break;
	case 1: tempScore = 800;
		break;
	case 2: tempScore = 600;
		break;
	case 3: tempScore = 400;
		break;
	case 4: tempScore = 200;
		break;
	case 5: tempScore = 0;
		break;
	case 6: tempScore = -100;
		break;
	case 7: tempScore = -200;
		break;
	case 8: tempScore = -300;
		break;
	case 9: tempScore = -400;
		break;
	case 10: tempScore = -500;
		break;
		
	}
	return tempScore;
}

int Fight::calculateTrueScore(int wins) // Add exceptions to escape
{
	int tempScore;
	
	switch (wins)
	{
	case 0: tempScore = 1000;
		break;
	case 1: tempScore = 600;
		break;
	case 2: tempScore = 340;
		break;
	case 3: tempScore = 320;
		break;
	case 4: tempScore = 220;
		break;
	case 5: tempScore = 100;
		break;
	case 6: tempScore = -100;
		break;
	case 7: tempScore = -235;
		break;
	case 8: tempScore = -250;
		break;
	case 9: tempScore = -400;
		break;
	case 10: tempScore = -550;
		break;

		
	}
	return tempScore;
}

void Fight::addOutsidePicks()
{
	int readerPicks = 0;
	int workingScore = 0;

	cout << endl << "Do you have outside input?" << endl;
	string input;
	cin >> input;
	if (find(affirmative.begin(), affirmative.end(), input) != affirmative.end())
	{
		cout << endl << "How many outside picks do you have?" << endl;
		cin >> totalPicks;
		cout << endl << "How many people picked " << nameOne << " to win?" << endl;
		cin >> pickedFirst;
		input = ".";
		cout << endl << "Do you have a reader poll?" << endl;
		cin >> input;
		while (find(affirmative.begin(), affirmative.end(), input) != affirmative.end())
		{
			totalPicks += READER_POLL_WEIGHT;
			cout << endl << "What percentage of readers picked " << nameOne << " to win?" << endl;
			cin >> readerPicks;
			pickedFirst += readerPicks * .01 * READER_POLL_WEIGHT;

			cout << endl << "Do you want to add another reader poll?" << endl;
			input.clear();
			cin >> input;
		}
		/*
		if (picksOne == totalPicks)
		{
			tempScoreOne = -100 * totalPicks;
			tempScoreTwo = 100 * totalPicks;
		}
		else if (picksOne == 0)
		{
			tempScoreOne = 100 * totalPicks;
			tempScoreTwo = -100 * totalPicks;
		}
		else if (picksOne >= totalPicks / 2)
		{
			tempScoreOne = (picksOne / picksTwo) * -100;
			tempScoreTwo = 100 / (picksTwo / picksOne);
		}
		else
		{
			tempScoreOne = 100 / (picksOne / picksTwo);
			tempScoreTwo = (picksTwo / picksOne) * -100;
		}
		(tempScoreOne > 0) ? outsideScoreOne = tempScoreOne * OUTSIDE_PICKS_MIN_ACCURACY : outsideScoreOne = tempScoreOne * OUTSIDE_PICKS_MAX_ACCURACY;
		(tempScoreTwo > 0) ? outsideScoreTwo = tempScoreTwo * OUTSIDE_PICKS_MIN_ACCURACY : outsideScoreTwo = tempScoreTwo * OUTSIDE_PICKS_MIN_ACCURACY;
		*/

		workingScore = mainOutsideAlgorithm(totalPicks, pickedFirst);

		int secondAlgorithm = secondOutsideAlgorithm(totalPicks, pickedFirst);
		if (workingScore > 0 && workingScore > secondAlgorithm)
			workingScore = secondAlgorithm;
		else if (workingScore < 0 && workingScore < secondAlgorithm)
			workingScore = secondAlgorithm;

		int thirdAlgorithm = thirdOutsideAlgorithm(totalPicks, pickedFirst);
		if (workingScore > 0 && workingScore > thirdAlgorithm)
			workingScore = thirdAlgorithm;
		else if (workingScore < 0 && workingScore < thirdAlgorithm)
			workingScore = thirdAlgorithm;



		if (mixedScoreOne) mixedScoreOne += workingScore * OUTSIDE_WEIGHT * totalPicks;
		if (mixedScoreTwo) mixedScoreTwo += -workingScore * OUTSIDE_WEIGHT * totalPicks;
		if (mixedSafeScoreOne) mixedSafeScoreOne += workingScore * OUTSIDE_WEIGHT * totalPicks;
		if (mixedSafeScoreTwo) mixedSafeScoreTwo += -workingScore * OUTSIDE_WEIGHT * totalPicks;
		mixedIndex += OUTSIDE_WEIGHT * totalPicks;

		if (workingScore > 0)
		{
			outsideScoreOne = workingScore * OUTSIDE_PICKS_MIN_ACCURACY;
			outsideSafeScoreOne = workingScore * OUTSIDE_PICKS_MIN_ACCURACY;
			outsideScoreTwo = -workingScore * OUTSIDE_PICKS_MAX_ACCURACY;
			outsideSafeScoreTwo = -workingScore * OUTSIDE_PICKS_MIN_ACCURACY;
		}
		if (workingScore < 0)
		{
			outsideScoreOne = workingScore * OUTSIDE_PICKS_MAX_ACCURACY;
			outsideSafeScoreOne = workingScore * OUTSIDE_PICKS_MIN_ACCURACY;
			outsideScoreTwo = -workingScore * OUTSIDE_PICKS_MIN_ACCURACY;
			outsideSafeScoreTwo = -workingScore * OUTSIDE_PICKS_MAX_ACCURACY;
		}		


		printOdds();
	}
}

int Fight::mainOutsideAlgorithm(double total, double wins)
{
	if (wins == 0)
		return MAX_OUTSIDE_ODDS;
	if (wins == total)
		return -MAX_OUTSIDE_ODDS;
	if (wins * 2 == total)
		return 0;
	if (wins * 2 > total)
		return -100 * (wins / (total - wins));
	else return 100 / (wins / (total - wins));
}

int Fight::secondOutsideAlgorithm(double total, double wins)
{
	if (wins == 0)
		return 150 + (total * 100);
	if (wins == total)
		return -150 - (total * 100);
	if (wins * 2 == total)
		return 0;
	if (wins * 2 > total)
		return -wins * ((300 + (total * 7)) / total);
	else return (total - wins) * ((300 + (total * 7)) / total);
}

int Fight::thirdOutsideAlgorithm(double total, double wins)
{
	if (wins == 0)
		return 700 + (total * 10);
	if (wins == total)
		return -700 - (total * 10);
	if (wins * 2 > total)
		return -wins * (MAX_OUTSIDE_ODDS / total);
	else return (total - wins) * (MAX_OUTSIDE_ODDS / total);
}

/*void Fight::addOtherInput()
{
	int value = 0;
	cout << endl << "Do you have other input to include?" << endl;
	string input;
	cin >> input;
	if (input == "y" || input == "yes" || input == "+")
	{
		cout << "How much would you like to add to " << nameOne << "'s score?" << endl;
		cin >> value;

		okayScoreOne += -value;
		scoreOne += -value;
		safeScoreOne += -value;

		cout << "How much would you like to add to " << nameTwo << "'s score?" << endl;
		cin >> value;
		okayScoreTwo += -value;
		scoreTwo += -value;
		safeScoreTwo += -value;

		cout << "How much would you like to add to the confidence index?" << endl;
		cin >> value;
		totalIndex += value;

		printOdds();
	}



}*/

/*void Fight::addFightPick()
{
	int value = 244 * WEIGHT * 5;
	cout << endl << "Do you have other input to include?" << endl;
	string input;
	cin >> input;
	if (input == "y" || input == "yes")
	{
		cout << "Who is predicted to win?" << endl << "Enter 1 for " << nameOne << endl << "Enter 2 for " << nameTwo << endl;
		do
			cin >> input; 
		while (input != "1" && input != "2");
		if (input == "1")
		{
			okayScoreOne += -value;
			scoreOne += -value;
			safeScoreOne += -value;
			okayScoreTwo += value;
			scoreTwo += value;
			safeScoreTwo += value;
		}
		if (input == "2")
		{
			okayScoreOne += value;
			scoreOne += value;
			safeScoreOne += value;
			okayScoreTwo += -value;
			scoreTwo += -value;
			safeScoreTwo += -value;
		}
	}
}*/

void Fight::saveToFile()
{
	double firstPercentage = 100 * pickedFirst / totalPicks;
	double secondPercentage = 100 * (totalPicks - pickedFirst) / totalPicks;
	cout.setf(std::ios::showpos);
	ofstream shortFile("TrueOddsTest.dat", ios::app);
	ofstream TESTweightFile("WeightTest.dat", ios::app);
	/*
	shortFile << "\n\nPicks: " << numberOfPicks << "\n" << nameOne << ": " << llround(scoreOne / weightIndex) << "\t" << llround(safeScoreOne / weightIndex) <<
		"\t" << llround(outsideScoreOne) << "\t" << llround(outsideSafeScoreOne) << "\t" <<
		llround(mixedScoreOne / mixedIndex) << "\t" << llround(mixedSafeScoreOne / mixedIndex) <<
		"\t" << llround(alternateScoreOne / weightIndex) << "\t" << llround(alternateSafeScoreOne / weightIndex) << "\n" <<
		nameTwo << ": " << llround(scoreTwo / weightIndex) << "\t" << llround(safeScoreTwo / weightIndex) << "\t" <<
		llround(outsideScoreTwo) << "\t" << llround(outsideSafeScoreTwo) << "\t" <<
		llround(mixedScoreTwo / mixedIndex) << "\t" << llround(mixedSafeScoreTwo / mixedIndex) <<
		"\t" << llround(alternateScoreTwo / weightIndex) << "\t" << llround(alternateSafeScoreTwo / weightIndex);
		*/

	shortFile << "\n\nPicks: " << numberOfPicks << "\n" << nameOne << ": "
		<< llround(scoreOne / weightIndex) << "\t" 
		<< llround(safeScoreOne / weightIndex) << "\t"
		<< llround(alternateScoreOne / weightIndex) << "\t"
		<< llround(alternateSafeScoreOne / weightIndex) << "\t" 
		<< llround(trueScoreOne / numberOfPicks) << "\t" 
		<< llround(trueScoreOneExtra / (numberOfPicks + picksAgainstOne)) << "\n"
		<< nameTwo << ": "
		<< llround(scoreTwo / weightIndex) << "\t"
		<< llround(safeScoreTwo / weightIndex) << "\t" 
		<< llround(alternateScoreTwo / weightIndex) << "\t"
		<< llround(alternateSafeScoreTwo / weightIndex) << "\t"
		<< llround(trueScoreTwo / numberOfPicks) << "\t" 
		<< llround(trueScoreTwoExtra / (numberOfPicks + picksAgainstTwo));
	

	longFile << "\n\t\t[Confidence: " << confidenceIndex << "]" << endl <<
		"\t\t[r/UFCTool Picks: " << numberOfPicks << "]" << endl <<
		//"\t\t[Outside Picks: " << totalPicks << "]" << endl <<
		"\n\t" << nameOne <<
		//"\n\t Good Bet: " << llround(scoreOne / weightIndex) <<
		"\n\t Okay Bet: " << llround((scoreOne / weightIndex) + 230) <<
		"\n\t Good Bet : " << llround((safeScoreOne / weightIndex) + 150) <<
		"\n\t Safe Bet : " << llround((safeScoreOne / weightIndex) + 220);
		// "\n\t Outside Score: " << llround(outsideScoreOne) <<
	if (totalPicks > 0) longFile << setprecision(3) << "\n\t Outside Support: " << firstPercentage << "% from " << totalPicks << " picks";
	longFile << "\n\n\t" << nameTwo <<
		//"\n\t Good Bet: " << llround(scoreTwo / weightIndex) <<
		"\n\t Okay Bet: " << llround((scoreTwo / weightIndex) + 230) <<
		"\n\t Good Bet : " << llround((safeScoreTwo / weightIndex) + 150) <<
		"\n\t Safe Bet : " << llround((safeScoreTwo / weightIndex) + 220);
		// "\n\t Outside Score: " << llround(outsideScoreTwo) <<
	if (totalPicks > 0) longFile << setprecision(3) << "\n\t Outside Support: " << secondPercentage << "% from " << totalPicks << " picks";
	longFile << "\n\n----------\n";



	TESTweightFile << endl << endl << endl << nameOne << ": ";
	for (int i = 0; i <= 10; ++i)
	{
		TESTweightFile << llround(TESTscoreOne[i] / TESTindexes[i]) << "\t";
		
	}

	TESTweightFile << endl << nameTwo << ": ";
	for (int i = 0; i <= 10; ++i)
	{
		TESTweightFile << llround(TESTscoreTwo[i] / TESTindexes[i]) << "\t";
	}

}

void Fight::pickBets()
{
	
	
}

// differential^differentialWeight * picks^picksWeight

string Fight::getNameOne()
{
	return nameOne;
}

void Fight::setNameOne(string name)
{
	nameOne = name;
}

string Fight::getNameTwo()
{
	return nameTwo;
}

void Fight::setNameTwo(string name)
{
	nameTwo = name;
}

int Fight::getScoreOne()
{
	return scoreOne;
}

void Fight::setScoreOne(int score)
{
	scoreOne = score;
}

int Fight::getScoreTwo()
{
	return scoreTwo;
}

void Fight::setScoreTwo(int score)
{

}