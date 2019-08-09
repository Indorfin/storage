// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::setprecision;
using std::llround;
using std::find;
using std::vector;
using std::ios;
using std::ofstream;

//const int MAX_CONFIDENCE_INDEX = 5;
const double SCORE_MODIFIER = 0.05;
const double CONFIDENCE_INDEX_MODIFIER = .1;
const int NUMBER_OF_FIGHTS = 10;
const double WEIGHT = .8;
const double OUTSIDE_WEIGHT = .04;
const int NUMBER_OF_STAFF_PICKS = 14;
const double OUTSIDE_PICKS_MAX_ACCURACY = .700;
const double OUTSIDE_PICKS_MIN_ACCURACY = .400;
const int MAX_OUTSIDE_ODDS = 1000;
const double READER_POLL_WEIGHT = 5;