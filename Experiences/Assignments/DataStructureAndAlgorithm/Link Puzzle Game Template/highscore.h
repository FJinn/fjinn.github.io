#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <iostream>
#include "windows.h"
#include <ctime>
#include "conio_yp.h"
#include <cmath>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

void displayScores(const int maxPlayer);
void sort(string names[], int scores[], const int maxPlayer);
void setHighscore(int level, string pName, int score);
void HighScoreMenu();

#endif
