#include "graphics.h"
#include <allegro5/allegro_ttf.h>

int main() {
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

	// variables
	bool done = false;
	int pos_x = width / 2;
	int pos_y = height / 2;
	bool gameover = false;
	int guess = 1;
	int coordX, coordY;
	bool draw = false;
	board b;
	graphics g(height, width, &b);

	// initializing
	al_init_primitives_addon();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();

	// allegro variables
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;
	ALLEGRO_FONT* font = al_load_font("AppleGaramond.ttf", 24, 0);

	if (!font) {
		fprintf(stderr, "Failed to initialize font.");
		return -1;
	}

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());

	// draw the board
	g.drawBoard();
	g.drawScore(b.getScore(), font);
	al_flip_display();

	// game loop
	while (!done)
	{
		if (guess <  3) {
			// wait for mouse click
			al_wait_for_event(event_queue, &ev);

			// establish mouse coords
			if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				pos_x = ev.mouse.x;
				pos_y = ev.mouse.y;
				coordX = g.getCoord(pos_x, "x");
				coordY = g.getCoord(pos_y, "y");

				// flip clicked card
				if (!b.flipCard(coordX, coordY, guess)) {
					draw = false;
				}
				else {
					guess++;
					if (guess > 3) {
						guess = 1;
					}
					draw = true;
				}
			}
		}
		else {
			// guesses are filled
			if (!b.checkGuess(*b.getA(), *b.getB())) {
				g.drawBoard();
				g.drawCards();
				g.drawScore(b.getScore(), font);
				al_flip_display();
				al_clear_to_color(al_map_rgb(0, 0, 0));
				// if its a wrong guess, pause before cleaning the card
				al_rest(5);
			}
			guess = 1;
			draw = true;
		}

		// redraw board
		if (draw) {
			g.drawBoard();
			g.drawCards();
			g.drawScore(b.getScore(), font);
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}

		// once all cards are matched
		if (b.getScore() >= 12) {
			done = true;
		}

	}

	while (done) {
		al_draw_filled_rectangle(0, height - 30, width, height, al_map_rgb(148, 192, 212));
		al_draw_line(0, height - 30, width, height - 30, al_map_rgb(255, 255, 255), 2);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, height - 29, 0, "Found all matches!");
		al_flip_display();
	}

	// cleanup
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	system("pause");
	return 0;
}