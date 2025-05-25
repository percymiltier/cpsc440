#ifndef LOGIC1_H
#define LOGIC1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class logic1 {

public:
	logic1();
	void nextWord(int wordsize);
	bool answer(string userW, string answer);
	string scramble(string word);
	string toString(char* a, int size);
	char* toCharArray(string a);

	// getters 
	const string getText() { return text; }
	const int textLength() { return text.length(); }
	const string getScramble() { return scrambleText; }
	const int getScore() { return score; }
	const vector<string> getSW() { return sWords; }
	const vector<string> getMW() { return mWords; }
	const vector<string> getLW() { return lWords; }
	const string getRandomSW() { return sWords[rand()%sWords.size()]; }
	const string getRandomMW() { return mWords[rand() % mWords.size()]; }
	const string getRandomLW() { return lWords[rand() % lWords.size()]; }

	// setters 
	const void updateText(string n) { text = n; }
	const void updateScramble(string n) { scrambleText = n; }
	const void updateScore(int n) { score = +n; }
	const void addSW(string word) { sWords.push_back(word); }
	const void addMW(string word) { mWords.push_back(word); }
	const void addLW(string word) { lWords.push_back(word); }

private:
	string text;
	string scrambleText;
	int score;
	vector<string> sWords;
	vector<string> mWords;
	vector<string> lWords;

};

#endif