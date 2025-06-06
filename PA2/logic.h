
#pragma once
#ifndef LOGIC_H
#define LOGIC_H

#include <stdlib.h>

class card {
public:
	card();
	card(int cx, int cy);

	bool cardEquals(card B);

	// getters
	int getShape();
	bool getFlipped();
	bool getMatch();
	int getX();
	int getY();

	// setters
	void setShape(int newshape);
	void setFlipped(bool flip);
	void setMatch(bool newmatch);
	void setCoords(int newx, int newy);
private:
	bool flipped;
	int shape;
	bool match;
	int x;
	int y;
};

class board {
public:
	board();
	bool checkGuess(card* guessA, card* guessB);
	bool flipCard(int y, int x, int guess);

	// getters
	card* getCard(int i, int j);
	int getScore();
	card* getA();
	card* getB();
private:
	card* guessA;
	card* guessB;
	card* answerkey[5][5];
	int score;
};

#endif