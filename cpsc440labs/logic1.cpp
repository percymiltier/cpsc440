#include "logic1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// constructor
logic1::logic1() {
	string in;

	// file init
	ifstream dictionary("dictionary.txt");

	// populate lists
	while (getline(dictionary, in)) {
		if (in.length() < 6) {
			addSW(in);
		}
		else if (in.length() > 5 && in.length() < 8) {
			addMW(in);
		}
		else {
			addLW(in);
		}
	}

	dictionary.close();

	score = 0;
}

// get next word, 1 == small word, 2 == medium word, 3 == large word
void logic1::nextWord(int wordsize) {
	if (wordsize == 1) {
		text = getRandomSW();
		scrambleText = scramble(text);
	}
	else if (wordsize == 2) {
		text = getRandomMW();
		scrambleText = scramble(text);
	}
	else if (wordsize == 3) {
		text = getRandomLW();
		scrambleText = scramble(text);
	}
}

// take user input, and add to the score
bool logic1::answer(string userW, string answer) {
	if (userW == answer) {
		updateScore(1);
		return true;
	}
	else {
		return false;
	}
}

// scramble the given word
string logic1::scramble(string word) {
	string scrambleText = word;
	random_shuffle(scrambleText.begin(), scrambleText.end());
	return scrambleText;
}

// convert a char array to a string
string logic1::toString(char* a, int size) {
	string s;
	for (int i = 0; i < size; i++) {
		s = s + a[i];
	} 
	return s;
}

// convert a string to a char array
char* logic1::toCharArray(string a) {
	int i = a.length();
	char** temp = new char*[i+1];
	*temp = _strdup(a.c_str());
	return *temp;
}