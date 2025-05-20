#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>

int main(int argc, char** argv) {

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


	bool done = false;

	// mouse coords
	int pos_x = width / 2;
	int pos_y = height / 2;

	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_EVENT ev;

	al_init_primitives_addon();
	al_install_mouse();

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_mouse_event_source());

	// game loop
	while (!done)
	{
		al_wait_for_event(event_queue, &ev);

		// establish mouse coords
		if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			pos_x = ev.mouse.x;
			pos_y = ev.mouse.y;
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