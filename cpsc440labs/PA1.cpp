#include <allegro5/allegro.h>
#include <cstdio>
#include <allegro5/allegro_native_dialog.h>
#include "labRunner.h"
#include <iostream>
#include <fstream>
#include "logic.h"
using namespace std;

void* input(ALLEGRO_THREAD* ptr, void* arg);
void* timer(ALLEGRO_THREAD* ptr, void* arg);

bool finished = false;
bool timeOut = false;
logic game;

int pa1() {

	ALLEGRO_THREAD* create1 = NULL, * create2 = NULL; //used for return value from thread creation

	create1 = al_create_thread(input, NULL);
	create2 = al_create_thread(timer, NULL);

	while (!finished && !timeOut)
	{


		if (!finished && !timeOut)
		{
			al_start_thread(create1);

			al_start_thread(create2);

		}
		else
		{
			al_destroy_thread(create1);
			al_destroy_thread(create2);
		}


	}
	if (finished) {
		cout << "\nYou got all 5 words correct! Congratulations!\n";
	}
	else {
		cout << "\nTime's up!\n";
		cout << "Final score: \n" << game.getScore();
		int i = game.getScore();

		if (i < 3) {
			cout << "Lowest intelligence... better luck next time.\n";
		}
		else if (i < 4) {
			cout << "Getting better...\n";
		}
		else if (i < 5) {
			cout << "Not bad!";
		}
	}
	
	system("pause");
	return 0;
}

// A pointer to a function that prompts the user for input
void* input(ALLEGRO_THREAD* ptr, void* arg)
{
	// logic init
	int turn = 0;
	string in;

	// game loop
	while (!finished)
	{
		// choose a new word
		if (turn < 2) {
			game.setWord(game.chooseWord(1, game));
		}
		else if (turn < 4) {
			game.setWord(game.chooseWord(2, game));
		}
		else {
			game.setWord(game.chooseWord(3, game));
		}
		turn++;
		if (turn > 5) {
			finished = true;
			break;
		}

		// scramble the word and take input
		game.setScramble(game.scrambleWord(game.getWord()));
		cout << game.getScramble() << "\n\nEnter your guess:\n";
		cin >> in;

		while (in != game.getWord()) {
			cout << "\nTry again:\n";
			cin >> in;
		}

		// add to score once its correct
		game.setScore(game.getScore() + 1);
	}
	return NULL;
}

// A pointer to a function that starts the timer and checks the change in
// finished, which is in the input thread.
void* timer(ALLEGRO_THREAD* ptr, void* arg)
{
	time_t startTime, currentTime; //times used to measure elapsed time
	startTime = time(NULL);
	currentTime = time(NULL);
	while (currentTime - startTime < 60 && !finished)
	{
		currentTime = time(NULL);
	}
	timeOut = true;
	return NULL;
}