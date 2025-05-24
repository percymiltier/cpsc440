#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>
#include "labRunner.h"

int lab2() {

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

	// establish coords
	bool done = false;
	int pos_x = width / 2;
	int pos_y = height / 2;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;

	al_init_primitives_addon();
	al_install_keyboard();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	// game loop
	while (!done)
	{
		al_wait_for_event(event_queue, &ev);

		// establish key commands
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				pos_y -= 10;
				break;
			case ALLEGRO_KEY_DOWN:
				pos_y += 10;
				break;
			case ALLEGRO_KEY_RIGHT:
				pos_x += 10;
				break;
			case ALLEGRO_KEY_LEFT:
				pos_x -= 10;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				done = true;
		}

		// draw cute object :-)
		al_draw_filled_circle(pos_x, pos_y, 40, al_map_rgb(252, 210, 81));
		al_draw_filled_ellipse(pos_x, pos_y + 8, 22, 17, al_map_rgb(0, 0, 0));
		al_draw_filled_ellipse(pos_x, pos_y + 2, 30, 17, al_map_rgb(252, 210, 81));
		al_draw_filled_circle(pos_x - 15, pos_y - 10, 5, al_map_rgb(0, 0, 0));
		al_draw_filled_circle(pos_x + 15, pos_y - 10, 5, al_map_rgb(0, 0, 0));
		al_flip_display();
		al_clear_to_color(al_map_rgb(253, 252, 249));
	}

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}