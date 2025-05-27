#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>
#include "labRunner.h"

struct map
{
	int x, y;
	int dir;
	int color;
} map;

void create_map(ALLEGRO_BITMAP *bmp[], ALLEGRO_DISPLAY *display);

int lab5() {

	ALLEGRO_BITMAP* bmp[1] = { NULL };
	//variables
	int width = 640;
	int height = 480;
	bool done = false;

	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;


	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	create_map(bmp, display);


	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		al_draw_bitmap(bmp[0], width / 2, 100, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	al_destroy_bitmap(bmp[0]);

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}

void create_map(ALLEGRO_BITMAP* bmp[], ALLEGRO_DISPLAY* display) {
		// bitmap creation
		bmp[0] = al_create_bitmap(64,64);
		if (!bmp[0]) {
			exit(1);
			al_destroy_display(display);
		}

		al_set_target_bitmap(bmp[0]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		int x = 32;
		int y = 20;


		// all my primatives
		al_draw_filled_ellipse(x, y, 8, 20, al_map_rgb(137, 137, 137));
		al_draw_filled_circle(x, y - 5, 5, al_map_rgb(115, 196, 242));
		al_draw_filled_triangle(x, y + 20, x + 12, y + 20, x + 12, y + 40, al_map_rgb(229, 38, 38));
		al_draw_filled_triangle(x, y + 20, x - 12, y + 20, x - 12, y + 40, al_map_rgb(229, 38, 38));
		al_draw_filled_rectangle(x - 5, y + 20, x + 5, y + 25, al_map_rgb(229, 38, 38));
		al_draw_filled_circle(x, y + 32, 5, al_map_rgb(255, 239, 74));
		al_draw_filled_triangle(x - 5, y + 32, x + 5, y + 32, x, y + 45, al_map_rgb(255, 239, 74));
}