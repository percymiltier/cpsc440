#include "logic.h"
#include <stdlib.h>

// board functions

// constructor
board::board() {
	// fill answer key with cards
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			card c(i, j);
			answerkey[i][j] = c;
		}
	}
	// set up card matches
	for (int i = 0; i < 12; i++) {
		// pick cards randomly
		int xA = rand() % 5;
		int yA = rand() % 5;
		int xB = rand() % 5;
		int yB = rand() % 5;
		card A = answerkey[xA][yA];
		card B = answerkey[xB][yB];
		// if card doesn't already have a match & cards aren't the same
		if ((!A.hasMatch()) && (xA != xB || yA != yB)) {
			// set matching card shapes
			A.setShape(i);
			B.setShape(i);
			// set matches
			A.setMatch(&B);
			B.setMatch(&A);
			// send cards back to board
			answerkey[xA][yA] = A;
			answerkey[xB][yB] = B;
		}
	}
}
// returns whether 2 cards match
bool board::checkGuess(card guessA, card guessB) {
	if (guessA.getShape() == guessB.getShape()) {
		// update score if there was a match
		score++;

		return true;
	}
	else {
		// flip cards back
		guessA.setFlipped(false);
		guessB.setFlipped(false);
		
		return false;
	}
}
// flip a card and make a guess
bool board::flipCard(int x, int y, int guess) {
	if (guess == 1 && answerkey[x][y].getFlipped() == false) {
		guessA = &answerkey[x][y];
		answerkey[x][y].setFlipped(true);
		return true;
	}
	else if (guess == 2 && answerkey[x][y].getFlipped() == false) {
		guessB = &answerkey[x][y];
		answerkey[x][y].setFlipped(true);
		return true;
	}
	else if (guess > 2) {
		checkGuess(*guessA, *guessB);
		return true;
	}
	else {
		return false;
	}
}
// getters
card board::getCard(int i, int j) {
	return answerkey[i][j];
}
int board::getScore() {
	return score;
}

// card functions

// constructors
card::card() {
	x = 0;
	y = 0;
	shape = NULL;
	flipped = false;
	match = NULL;
}
card::card(int cx, int cy) {
	x = cx;
	y = cy;
	shape = NULL;
	flipped = false;
	match = NULL;
}
// returns if the card has a match or not already
bool card::hasMatch() const {
	if (match == NULL) {
		return false;
	}
	else return true;
}
// setters
void card::setShape(int newshape) {
	shape = newshape;
}
void card::setFlipped(bool flip) {
	flipped = flip;
}
void card::setMatch(card* newmatch) {
	match = newmatch;
}
// getters 
int card::getShape() {
	return shape;
}
bool card::getFlipped() {
	return flipped;
}
card* card::getMatch() {
	return match;
}
int card::getX() {
	return x;
}
int card::getY() {
	return y;
}
// ops
bool card::cardEquals(card B) {
	if (shape == B.getShape() &&
		flipped == B.getFlipped() &&
		match == B.getMatch() &&
		x == B.getX() &&
		y == B.getY()) {
		
		return true;
	}
	else {
		return false;
	}
}