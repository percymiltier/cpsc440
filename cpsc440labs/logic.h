#ifndef LOGIC1_H
#define LOGIC1_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class logic {

public:
	logic();
	
	string scrambleWord(string n);
	string chooseWord(int level, logic game);

	// setter
	void setWord(string n);
	void setScramble(string n);
	void setScore(int n);

	//getter
	string getWord();
	string getScramble();
	vector<string> getSW();
	vector<string> getMW();
	vector<string> getLW();
	int getScore();

private:
	string word;
	string scramble;
	vector<string> sWords;
	vector<string> mWords;
	vector<string> lWords;
	int score;

};

#endif
