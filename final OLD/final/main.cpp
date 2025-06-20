#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "player.h"
#include "mappy_A5.h"
#include <iostream>
using namespace std;

int collided(int x, int y);  //Tile Collision
bool endValue(int x, int y); //End Block with the User Value = 8

int main(void)
{
	const int WIDTH = 448;
	const int HEIGHT = 448;
	const int BLOCKHEIGHT = 32;
	bool keys[] = { false, false, false, false, false };
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	//variables
	bool done = false;
	int level = 1;
	bool render = false;
	bool levelOver = false;
	int counter = 0;
	int direction;
	//Player Variable
	player myplayer;


	// font
	al_init_font_addon();
	al_init_ttf_addon();


	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	myplayer.initPlayer(WIDTH, HEIGHT);

	int xOff = 0;
	int yOff = 0;
	if (MapLoad("level1.fmp", 1))
		return -5;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	ALLEGRO_FONT* font24 = al_load_font("BondTime.ttf", 30, 0);

	if (!font24) {
		fprintf(stderr, "Failed to initialize font.");
		return -1;
	}

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	//draw the background tiles
	MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);

	//draw foreground tiles
	MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
	myplayer.drawPlayer(0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	while (!done)
	{

		// reaching the goal
		if (myplayer.CollisionEndBlock()) {
			levelOver = true;
		}

		// next level
		if (levelOver && level <= 3) {
			levelOver = false;
			level++;
			timer = 0;
			counter = 0;
			int xOff = 0;
			int yOff = 0;
			myplayer.setX(64);
			myplayer.setY(64);
			switch (level) {
			case 1:
				if (MapLoad("level1.fmp", 1))
					return -5;
				break;
			case 2:
				if (MapLoad("level2.fmp", 1))
					return -5;
				break;
			case 3:
				if (MapLoad("level3.fmp", 1))
					return -5;
				break;
			}
		}

		counter++;

		// check timer
		if (counter / 60 > 60) {
			// if taken longer than 1 minute to complete the maze
			done = true;
			break;
		}
		// check gameover
		if (level > 3) {
			done = true;
			break;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			// movement
			if (keys[UP]) {
				myplayer.moveUp();
			}
			else if (keys[DOWN]) {
				myplayer.moveDown(HEIGHT);
			}
			else if (keys[LEFT]) {
				myplayer.moveLeft();
			}
			else if (keys[RIGHT]) {
				myplayer.moveRight(WIDTH);
			}

			// redraw screen
			render = true;

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
				direction = 0;
				myplayer.setMoving(true);
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				direction = 1;
				myplayer.setMoving(true);
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				direction = 2;
				myplayer.setMoving(true);
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				direction = 3;
				myplayer.setMoving(true);
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				myplayer.setMoving(false);
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				myplayer.setMoving(false);
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				myplayer.setMoving(false);
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				myplayer.setMoving(false);
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			}
		}

		// redraw screen here
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//update the map scroll position
			xOff = myplayer.getX() + myplayer.getWidth() - WIDTH / 2;
			yOff = myplayer.getY() + myplayer.getHeight() - HEIGHT / 2;

			//avoid moving beyond the map edge
			if (xOff < 0) xOff = 0;

			if (xOff > (mapwidth * mapblockwidth - WIDTH))
				xOff = mapwidth * mapblockwidth - WIDTH;
			if (yOff < 0)
				yOff = 0;
			if (yOff > (mapheight * mapblockheight - HEIGHT))
				yOff = mapheight * mapblockheight - HEIGHT;

			// animated tiles
			MapUpdateAnims();
			myplayer.updatePlayer(direction);

			MapChangeLayer(0);
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			MapChangeLayer(1);
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			myplayer.drawPlayer(xOff, yOff);

			// timer on screen
			if ((60 - (counter / 60)) > 10) {
				al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, 10, 0, "Time: %i", 60 - (counter / 60));
			}
			else {
				// warning text
				al_draw_textf(font24, al_map_rgb(245, 41, 8), 10, 10, 0, "Time: %i", 60 - (counter / 60));
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	// end of game

	MapFreeMem();
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}


int collided(int x, int y) // modified to get all collissions since we don't need to go through any blocks here
{
	BLKSTR* blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	if (blockdata->tl) {
		return blockdata->tl;
	}
	else if (blockdata->tr) {
		return blockdata->tr;
	}
	else if (blockdata->bl) {
		return blockdata->bl;
	}
	else if (blockdata->br) {
		return blockdata->br;
	}
	else {
		return false;
	}
}

bool endValue(int x, int y) // determines when the player reaches the end of a level
{

	BLKSTR* data;
	data = MapGetBlock(x / mapblockwidth, y / mapblockheight);

	if (data->user1 == 1)
	{
		return true;
	}
	else
		return false;
}