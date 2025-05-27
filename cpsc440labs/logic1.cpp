#include "logic1.h"
#include <fstream>
#include <iostream>

logic1::logic1() {
	word = "";
	scramble = "";
	score = 0;

	// read in words from file
	string in;
	ifstream dictionary("dictionary.txt");
	while (getline(dictionary, in)) {
		if (in.length() < 6) {
			sWords.push_back(in);
		}
		else if (in.length() > 5 && in.length() < 8) {
			mWords.push_back(in);
		}
		else {
			lWords.push_back(in);
		}
	}

	dictionary.close();
}

// scramble a word
string logic1::scrambleWord(string n) {
	string scrambleText = n;
	random_shuffle(scrambleText.begin(), scrambleText.end());
	return scrambleText;
}

// selects a word from the lists based on length, 1=S, 2=M, 3=L
string logic1::chooseWord(int level, logic1 game) {
	if (level == 1) {
		vector<string> temp = game.getSW();
		return temp[rand() % temp.size()];
	}
	else if (level == 2) {
		vector<string> temp = game.getMW();
		return temp[rand() % temp.size()];
	}
	else if (level == 3) {
		vector<string> temp = game.getLW();
		return temp[rand() % temp.size()];
	}
	else {
		return "";
	}
}



// setters
void logic1::setWord(string n) {
	word = n;
}

void logic1::setScramble(string n) {
	scramble = n;
}

void logic1::setScore(int n) {
	score = n;
}



// getters
string logic1::getWord() {
	return word;
}

string logic1::getScramble() {
	return scramble;
}

vector<string> logic1::getSW() {
	return sWords;
}

vector<string> logic1::getMW() {
	return mWords;
}

vector<string> logic1::getLW() {
	return lWords;
}

int logic1::getScore() {
	return score;
}