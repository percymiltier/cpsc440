#include "logic.h"
#include "graphics.cpp"
#include "labRunner.h"

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
	bool draw;
	graphics g = graphics(height, width);
	board b = board();

	// initializing
	al_init_primitives_addon();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();

	// allegro variables
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;
	ALLEGRO_FONT* font = al_load_font("AppleGaramond.ttf", 24, 0);

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());

	// draw the board
	g.drawBoard();
	g.drawScore(b.getScore(), font);
	al_flip_display();

	// game loop
	while (!done)
	{
		// wait for mouse click
		al_wait_for_event(event_queue, &ev);

		// establish mouse coords
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
			// flip clicked card
			coordX = g.getCoord(pos_x, "x");
			coordY = g.getCoord(pos_y, "y");

			if (!b.flipCard(coordX, coordY, guess)) {
				draw = false;
			}
			else {
				draw = true;
			}
		}

		if (draw) {
			// redraw board
			g.drawBoard();
			g.drawCards(b);
			g.drawScore(b.getScore(), font);
		}

	}

	// cleanup
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	system("pause");
	return 0;
}