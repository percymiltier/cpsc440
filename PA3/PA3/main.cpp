#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <cstdio>
#include "player.h"
#include "weapon.h"
#include "enemy.h"

int main(void)
{

	const int WIDTH = 800;
	const int HEIGHT = 473;
	const int NUM_weapon = 50;
	const int NUM_enemy = 10;
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	bool keys[5] = { false, false, false, false, false };


	//primitive variable
	bool done = false;
	bool redraw = true;
	const int FPS = 60;
	bool fire = false;

	// font
	al_init_font_addon();
	al_init_ttf_addon();

	//Allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	//Initialization Functions
	if (!al_init()) {
		return -1;
	}

	display = al_create_display(WIDTH, HEIGHT);

	if (!display) {
		return -1;
	}

	al_install_keyboard();
	al_init_image_addon();

	//object variables
	player myplayer(348, 360);
	weapon weapons[NUM_weapon];
	enemy enemies[NUM_enemy];

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	ALLEGRO_FONT* font24 = al_load_font("BondTime.ttf", 30, 0);

	if (!font24) {
		fprintf(stderr, "Failed to initialize font.");
		return -1;
	}

	srand(time(NULL));

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	ALLEGRO_BITMAP* bg = al_load_bitmap("bg.png");


	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;
			if (keys[LEFT])
				myplayer.moveLeft();
			if (keys[RIGHT])
				myplayer.moveRight();

			for (int i = 0;i < NUM_weapon;i++)
				weapons[i].updateWeapon(myplayer);
			for (int i = 0;i < NUM_enemy;i++)
				enemies[i].startEnemy(WIDTH);
			for (int i = 0;i < NUM_enemy;i++)
				enemies[i].updateEnemy(HEIGHT);
			for (int i = 0;i < NUM_weapon;i++)
				weapons[i].collideWeapon(enemies, NUM_enemy, &myplayer);
			for (int i = 0;i < NUM_enemy;i++)
				enemies[i].collideEnemy(&myplayer, HEIGHT);
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
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				fire = true;
				int i = 0;
				bool temp = false;
				do {
					weapons[i].setAngle(myplayer);
					temp = weapons[i].fireWeapon(myplayer);
					i++;
				} while (!temp);
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				fire = false;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_draw_bitmap(bg, 0, 0, 0);

			myplayer.drawPointer();

			if (fire) {
				myplayer.drawPlayer(1);
			}
			else {
				myplayer.drawPlayer(0);
			}


			for (int i = 0;i < NUM_weapon;i++)
				weapons[i].drawWeapon();
			for (int i = 0;i < NUM_enemy;i++)
				enemies[i].drawEnemy();

			al_draw_textf(font24, al_map_rgb(255, 208, 34), 10, 10, 0, "Health: %i/5", myplayer.getHealth());
			al_draw_textf(font24, al_map_rgb(231, 56, 22), 10, 45, 0, "Score: %i", myplayer.getScore());

			al_flip_display();
			al_clear_to_color(al_map_rgb(129, 227, 231));
		}

		if (myplayer.getHealth() == 0) {
			done = true;
		}
	}

	// draw final screen
	al_draw_bitmap(bg, 0, 0, 0);
	myplayer.drawPlayer(2);
	al_draw_textf(font24, al_map_rgb(231, 56, 22), 10, 10, 0, "You died! Final Score: %i", myplayer.getScore());

	al_flip_display();

	al_rest(5);

	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("Pause");
	return 0;
}