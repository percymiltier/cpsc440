#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>
#include <allegro5/allegro_native_dialog.h>
#include "labRunner.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <fstream>
#include "logic1.h"
using namespace std;

int pa1() {

	// set up allegro display
	ALLEGRO_DISPLAY* display = NULL;

	int width = 800;
	int height = 600;

	// check if allegro can start up
	if (!al_init()) {
		fprintf(stderr, "Failed to start Allegro.");
		return -1;
	}

	// create display
	display = al_create_display(width, height);
	if (!display) {
		fprintf(stderr, "Failed to create display.");
		return -1;
	}


	al_clear_to_color(al_map_rgb(250, 250, 250));

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT* font24 = al_load_font("AppleGaramond.ttf", 24, 0);

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// logic init
	logic1 game;
	bool next = true;
	bool result = false;
	int turn = 0;
	bool done = false;

	// game loop
	while (!done)
	{
		al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(250, 250, 250));

		// get next word
		int i = 0;
		if (i < 2 && next == true) {
			game.nextWord(1);
			turn++;
		}
		else if (i < 4 && next == true) {
			game.nextWord(2);
			turn++;
		}
		else if (next == true) {
			game.nextWord(3);
			turn++;
		}

		// end game on last word
		if (turn > 5) {
			done = true;
		}

		// draw scrambled word on screen
		al_draw_textf(font24, al_map_rgb(0, 0, 0), 50, 50, 0, game.toCharArray(game.getScramble()));

		// get user input
		char curr[50] = "";
		int pointer = 0;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					// submit word
					result = game.answer(game.toString(curr, strlen(curr)), game.getText());
					break;
				default:
					// add char to string
					curr[pointer] = ev.keyboard.unichar;
					pointer++;
					break;
			}
		}

		// success or failure
		if (result == true) {
			// correct answer
			next = true;
		}

		// display timer + score
		al_draw_textf(font24, al_map_rgb(0, 0, 0), 50, 80, 0, "%i", game.getScore());

	}

	// display final screen
	al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(250, 249, 248));
	al_draw_textf(font24, al_map_rgb(0, 0, 0), 50, 50, 0, "Final score: %i", game.getScore());
	if (game.getScore() <= 2) {
		al_draw_textf(font24, al_map_rgb(0, 0, 0), 50, 80, 0, "Lowest intelligence, better luck next time!");
	}
	else if (game.getScore() == 3) {
		al_draw_textf(font24, al_map_rgb(0, 0, 0), 50, 80, 0, "Getting better...");
	}
	else if (game.getScore() == 4) {
		al_draw_textf(font24, al_map_rgb(0, 0, 0), 50, 80, 0, "Pretty good!");
	}
	else if (game.getScore() > 4) {
		al_draw_textf(font24, al_map_rgb(0, 0, 0), 50, 80, 0, "Highest intelligence! Way to go!");
	}
	

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}