#include "logic.h"
#include <fstream>
#include <iostream>

logic::logic() {
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
string logic::scrambleWord(string n) {
	string scrambleText = n;
	random_shuffle(scrambleText.begin(), scrambleText.end());
	return scrambleText;
}

// selects a word from the lists based on length, 1=S, 2=M, 3=L
string logic::chooseWord(int level, logic game) {
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
void logic::setWord(string n) {
	word = n;
}

void logic::setScramble(string n) {
	scramble = n;
}

void logic::setScore(int n) {
	score = n;
}



// getters
string logic::getWord() {
	return word;
}

string logic::getScramble() {
	return scramble;
}

vector<string> logic::getSW() {
	return sWords;
}

vector<string> logic::getMW() {
	return mWords;
}

vector<string> logic::getLW() {
	return lWords;
}

int logic::getScore() {
	return score;
}