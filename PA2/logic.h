class board {
public:
	board();
	bool checkGuess(card guessA, card guessB);
	bool flipCard(int x, int y, int guess);

	// getters
	card getCard(int i, int j);
	int getScore();
private:
	card* guessA;
	card* guessB;
	card answerkey[5][5];
	int score;
};

class card {
public:
	card(int cx, int cy);

	bool hasMatch() const;
	bool cardEquals(card B);

	// getters
	int getShape();
	bool getFlipped();
	card* getMatch();
	int getX();
	int getY();

	// setters
	void setShape(int newshape);
	void setFlipped(bool flip);
	void setMatch(card* newmatch);
private:
	bool flipped;
	int shape;
	card* match;
	int x;
	int y;
};