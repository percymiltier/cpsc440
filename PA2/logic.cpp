#include "logic.h"

// board functions

// constructor
board::board() {
	// fill answer key with cards
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			answerkey[i][j] = new card(i, j);
		}
	}
	// set up card matches
	int i = 0;
	while (i < 12) {
		// pick cards randomly
		int xA = rand() % 5;
		int yA = rand() % 5;
		int xB = rand() % 5;
		int yB = rand() % 5;
		card* A = getCard(xA, yA);
		card* B = getCard(xB, yB);
		// if card doesn't already have a match & cards aren't the same
		if (!A->getMatch() && !B->getMatch() && !(xA == xB && yA == yB)) {
			// set matching card shapes
			A->setShape(i);
			B->setShape(i);
			// set matches
			A->setMatch(true);
			B->setMatch(true);
			i++;
		}
	}
	score = 0;
	guessA = nullptr;
	guessB = nullptr;
}
// returns whether 2 cards match
bool board::checkGuess(card* guessA, card* guessB) {
	if (guessA->getShape() == guessB->getShape()) {
		// update score if there was a match
		score++;

		return true;
	}
	else {
		// flip cards back
		guessA->setFlipped(false);
		guessB->setFlipped(false);

		guessA = nullptr;
		guessB = nullptr;
		
		return false;
	}
}
// flip a card and make a guess
bool board::flipCard(int y, int x, int guess) {
	// make sure card isn't already flipped over
	if (answerkey[x][y]->getFlipped() == false) {
		if (guess == 1) {
			guessA = answerkey[x][y];
			answerkey[x][y]->setFlipped(true);
			return true;
		}
		else if (guess == 2) {
			guessB = answerkey[x][y];
			answerkey[x][y]->setFlipped(true);
			return true;
		}
		else if (guess > 2) {
			checkGuess(guessA, guessB);
			return true;
		}
	}
	else {
		return false;
	}
}
// getters
card* board::getCard(int i, int j) {
	card* ptr = answerkey[i][j];
	return ptr;
}
int board::getScore() {
	return score;
}
card* board::getA() {
	return guessA;
}
card* board::getB() {
	return guessB;
}

// card functions

// constructors
card::card() {
	x = 0;
	y = 0;
	shape = NULL;
	flipped = false;
	match = false;
}
card::card(int cx, int cy) {
	x = cx;
	y = cy;
	shape = NULL;
	flipped = false;
	match = false;
}
// setters
void card::setShape(int newshape) {
	shape = newshape;
}
void card::setFlipped(bool flip) {
	flipped = flip;
}
void card::setMatch(bool newmatch) {
	match = newmatch;
}
// getters 
int card::getShape() {
	return shape;
}
bool card::getFlipped() {
	return flipped;
}
bool card::getMatch() {
	return match;
}
int card::getX() {
	return x;
}
int card::getY() {
	return y;
}
void card::setCoords(int newx, int newy) {
	x = newx;
	y = newy;
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