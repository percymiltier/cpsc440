#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "SpriteSheet.h"
#include "mappy_A5.h"
#include <iostream>
using namespace std;

int collided(int x, int y);  //Tile Collision
bool endValue( int x, int y ); //End Block with the User Value = 8
int main(void)
{
	const int WIDTH = 448;
	const int HEIGHT = 448;
	const int BLOCKHEIGHT = 32;
	bool keys[] = {false, false, false, false, false};
	enum KEYS{UP, DOWN, LEFT, RIGHT, SPACE};
	//variables
	bool done = false;
	int level = 1;
	bool render = false;
	bool levelOver = false;
	int counter = 0;
	//Player Variable
	Sprite player;


	// font
	al_init_font_addon();
	al_init_ttf_addon();


	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	player.InitSprites(WIDTH,HEIGHT);

	int xOff = 0;
	int yOff = 0;
	if(MapLoad("level1.fmp", 1))
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
	MapDrawBG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1);

	//draw foreground tiles
	MapDrawFG(xOff,yOff, 0, 0, WIDTH-1, HEIGHT-1, 0);
	player.DrawSprites(0,0);
	al_flip_display();
	al_clear_to_color(al_map_rgb(0,0,0));
	while(!done)
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
			int xOff = 0;
			int yOff = 0;
			player.setX(64);
			player.setY(64);
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
		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			// movement
			if (keys[UP]){
				player.moveUp(HEIGHT, BLOCKHEIGHT);
			}
			else if(keys[DOWN]) {
				player.moveDown(HEIGHT, BLOCKHEIGHT);
			}
			else if (keys[LEFT]) {
				player.moveLeft(WIDTH, BLOCKHEIGHT);
			}
			else if(keys[RIGHT]) {
				player.moveRight(WIDTH, BLOCKHEIGHT);
			}

			// redraw screen
			render = true;

		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
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
		else if(ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(ev.keyboard.keycode)
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
		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			//update the map scroll position
			xOff = player.getX()+player.getWidth() - WIDTH/2 ;
			yOff = player.getY()+player.getHeight()   - HEIGHT/2 ;

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

			MapChangeLayer(0);
			MapDrawBG(xOff,yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff,yOff, 0, 0, WIDTH, HEIGHT, 0);
			MapChangeLayer(1);
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
			MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
			player.DrawSprites(xOff, yOff);

			// timer on screen
			if ((60 - (counter / 60)) > 10) {
				al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, 10, 0, "Time: %i", 60 - (counter / 60));
			}
			else {
				// warning text
				al_draw_textf(font24, al_map_rgb(245, 41, 8), 10, 10, 0, "Time: %i", 60 - (counter / 60));
			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	// final screen 
	xOff = player.getX() + player.getWidth() - WIDTH / 2;
	yOff = player.getY() + player.getHeight() - HEIGHT / 2;
	if (xOff < 0) xOff = 0;
	if (xOff > (mapwidth * mapblockwidth - WIDTH))
		xOff = mapwidth * mapblockwidth - WIDTH;
	if (yOff < 0)
		yOff = 0;
	if (yOff > (mapheight * mapblockheight - HEIGHT))
		yOff = mapheight * mapblockheight - HEIGHT;
	MapChangeLayer(0);
	MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
	MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
	MapChangeLayer(1);
	MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);
	MapDrawFG(xOff, yOff, 0, 0, WIDTH, HEIGHT, 0);
	player.DrawSprites(xOff, yOff);

	// game over text
	if (level > 3) {
		// finished every level
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, 10, 0, "Game complete!");
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, 38, 0, "Thanks for playing!");
	}
	else {
		// didn't finish every level
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, 10, 0, "Game over!");
		al_draw_textf(font24, al_map_rgb(242, 187, 39), 10, 38, 0, "Final level: %i", level);
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
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x/mapblockwidth, y/mapblockheight);
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

bool endValue( int x, int y ) // determines when the player reaches the end of a level
{

	BLKSTR* data;
	data = MapGetBlock( x/mapblockwidth, y/mapblockheight );

	if( data->user1 == 1 )
	{
		return true;
	}else
		return false;
}