#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "fish.h"


int main(void)
{


	const int width = 900;
	const int height = 800;
	enum KEYS { UP, DOWN, LEFT, RIGHT };
	bool keys[4] = { false, false, false, false };

	//primitive variable
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	int dir = 0;


	//Allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if (!display)										//test display object
		return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_image_addon();

	//object variables
	fish fishie(width / 2, height / 2);


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* bg = al_load_bitmap("water.png");

	srand(time(NULL));

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_set_target_bitmap(al_get_backbuffer(display));
	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[UP]) {
				dir = 0;
				fishie.moveUp();
			}
			if (keys[DOWN]) {
				dir = 1;
				fishie.moveDown(height);
			}
			if (keys[LEFT]) {
				dir = 2;
				fishie.moveLeft();
			}
			if (keys[RIGHT]) {
				dir = 3;
				fishie.moveRight(width);
			}

		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = true;
				keys[DOWN] = false;
				keys[LEFT] = false;
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				keys[UP] = false;
				keys[LEFT] = false;
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				keys[UP] = false;
				keys[DOWN] = false;
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				keys[UP] = false;
				keys[DOWN] = false;
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[UP] = false;
				keys[DOWN] = false;
				keys[LEFT] = false;
				keys[RIGHT] = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(bg, 0, 0, 0);
			fishie.drawFish(width, height, dir);

			al_flip_display();
		}
	}

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}

// bg helpers





