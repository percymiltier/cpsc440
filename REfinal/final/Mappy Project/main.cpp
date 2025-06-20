#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro_acodec.h>

#include "sprite.h"
#include "enemy.h"
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
	const int ENEMYNUM = 10;
	bool keys[] = { false, false, false, false, false };
	enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };
	//variables
	bool titlescreen = true;
	bool done = false;
	int level = 1;
	bool render = false;
	bool levelOver = false;
	int counter = 0;
	bool dead = false;
	//Player Variables
	Sprite player;
	enemy enemies[ENEMYNUM];


	// font
	al_init_font_addon();
	al_init_ttf_addon();


	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer;
	ALLEGRO_SAMPLE* sample = NULL;
	ALLEGRO_BITMAP* carbie = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	if (!al_install_audio()) {
		return -1;
	}

	if (!al_init_acodec_addon()) {
		return -1;
	}

	if (!al_reserve_samples(4)) {
		return -1;
	}
	sample = al_load_sample("bgm.wav");

	if (!sample) {
		exit(9);
	}
	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	player.InitSprites(WIDTH, HEIGHT);

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

	// extra image
	carbie = al_load_bitmap("altcarbie.png");
	if (!carbie) {
		fprintf(stderr, "cant find carbie\n");
		exit(-2);
	}

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_play_sample(sample, 1.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);


	// title loop
	double angle = 1;
	double addsub = .1;
	int framedelay = 10;
	int framecount = 0;
	while (titlescreen) {
		// draw carbie
		al_draw_bitmap(carbie, WIDTH / 2 + 75, HEIGHT / 3, 0);

		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, 10, 0, "Press any key to start");
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, HEIGHT/2, 0, "Avoid touching the enemies");
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, (HEIGHT / 2) + 30, 0, "and reach the goal!");

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

		// press any key to continue
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			titlescreen = false;
		}
	}

	al_start_timer(timer);
	//draw the background tiles
	MapDrawBG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1);

	//draw foreground tiles
	MapDrawFG(xOff, yOff, 0, 0, WIDTH - 1, HEIGHT - 1, 0);
	player.DrawSprites(0, 0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0, 0, 0));
	while (!done)
	{

		// reaching the goal
		if (player.CollisionEndBlock()) {
			levelOver = true;
		}

		// next level
		if (levelOver && level <= 3) {
			levelOver = false;
			level++;
			timer = 0;
			counter = 0;
			xOff = 0;
			yOff = 0;
			player.setX(64);
			player.setY(64);
			switch (level) {
			case 1:
				if (MapLoad("level1.fmp", 1)) {
					return -5;
				}
				// reset enemies before setting up the new level
				for (int i = 0; i < ENEMYNUM; i++) {
					enemies[i].setLive(false);
				}
				// level 1 setup, has only 3 enemies
				enemies[0].initEnemy(true, 160, 192, 2, 0);
				enemies[1].initEnemy(true, 384, 192, 2, 0);
				enemies[2].initEnemy(true, 608, 192, 2, 0);

				break;
			case 2:
				if (MapLoad("level2.fmp", 1)) {
					return -5;
				}
				// reset enemies before setting up the new level
				for (int i = 0; i < ENEMYNUM; i++) {
					enemies[i].setLive(false);
				}
				// level 2 setup, has  5 enemies
				enemies[0].initEnemy(true, 224, 96, 2, 1);
				enemies[1].initEnemy(true, 96, 288, 2, 0);
				enemies[2].initEnemy(true, 512, 224, 2, 0);
				enemies[3].initEnemy(true, 704, 128, 2, 0);
				enemies[4].initEnemy(true, 640, 224, 2, 0);
				break;
			case 3:
				if (MapLoad("level3.fmp", 1)) {
					return -5;
				}
				// reset enemies before setting up the new level
				for (int i = 0; i < ENEMYNUM; i++) {
					enemies[i].setLive(false);
				}
				// level 2 setup, has  7 enemies
				enemies[0].initEnemy(true, 192, 96, 2, 1);
				enemies[1].initEnemy(true, 256, 288, 2, 0);
				enemies[2].initEnemy(true, 320, 224, 2, 0);
				enemies[3].initEnemy(true, 384, 128, 2, 0);
				enemies[4].initEnemy(true, 448, 224, 2, 0);
				enemies[5].initEnemy(true, 512, 224, 2, 0);
				enemies[6].initEnemy(true, 476, 224, 2, 0);
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
		if (player.getHP() <= 0) {
			done = true;
			dead = true;
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			// movement
			if (keys[UP]) {
				player.moveUp(HEIGHT, BLOCKHEIGHT);
			}
			else if (keys[DOWN]) {
				player.moveDown(HEIGHT, BLOCKHEIGHT);
			}
			else if (keys[LEFT]) {
				player.moveLeft(WIDTH, BLOCKHEIGHT);
			}
			else if (keys[RIGHT]) {
				player.moveRight(WIDTH, BLOCKHEIGHT);
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
				player.setMoving(true);
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = true;
				player.setMoving(true);
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				player.setMoving(true);
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				player.setMoving(true);
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
				player.setMoving(false);
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				player.setMoving(false);
				keys[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				player.setMoving(false);
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				player.setMoving(false);
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
			xOff = player.getX() + player.getWidth() - WIDTH / 2;
			yOff = player.getY() + player.getHeight() - HEIGHT / 2;

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
			player.UpdateSprites();
			for (int i = 0; i < ENEMYNUM; i++) {
				enemies[i].updateEnemy();
				enemies[i].hitSprite(player);
			}

			MapChangeLayer(0);
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			MapChangeLayer(1);
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			player.DrawSprites(xOff, yOff);
			for (int i = 0; i < ENEMYNUM; i++) {
				enemies[i].drawEnemy(xOff, yOff);
			}

			// health bar
			al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, HEIGHT - 30, 0, "HP:");
			al_draw_filled_rectangle(60, HEIGHT - 30, 110, HEIGHT - 6, al_map_rgb(255, 255, 255));
			al_draw_filled_rectangle(60, HEIGHT - 30, 60 + (player.getHP() * 10), HEIGHT - 6, al_map_rgb(0, 255, 0));

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

	// final screen
	al_draw_bitmap(carbie, WIDTH / 2 + 75, HEIGHT / 3, 0);

	if (dead) {
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, HEIGHT / 2, 0, "You died!");
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, (HEIGHT / 2) + 30, 0, "Final level: %i", level);
	}
	else {
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, HEIGHT / 2, 0, "Congratulations!");
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, (HEIGHT / 2) + 30, 0, "HP left: %i", player.getHP());
	}

	al_flip_display();
	// wait
	al_rest(10);


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