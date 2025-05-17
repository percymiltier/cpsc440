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
	display = al_create_display(width,height);
	if (!display) {
		fprintf(stderr, "Failed to create display.");
		return -1;
	}

	al_init_primitives_addon();
	al_clear_to_color(al_map_rgb(211, 232, 249));

	// sky color
	al_draw_filled_rectangle(0, 490, width, height, al_map_rgb(168, 212, 133));

	// drawing the house
	al_draw_filled_rectangle(250, 370, 550, 520, al_map_rgb(164, 117, 88));
	al_draw_filled_rectangle(275, 410, 345, 520, al_map_rgb(100, 71, 54));
	al_draw_filled_rectangle(380, 430, 520, 490, al_map_rgb(144, 173, 216));
	al_draw_filled_triangle(230, 370, 400, 270, 570, 370, al_map_rgb(184, 65, 65));

	al_flip_display();

	al_rest(20);
	al_destroy_display(display);
}