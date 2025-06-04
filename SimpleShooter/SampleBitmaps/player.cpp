#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"


player::~player()
{
	for (int i = 0; i < 4; i++) {
		al_destroy_bitmap(image[i]);
	}
}
player::player(int HEIGHT)
{

	for (int i = 0;i < 4; i++)
	{
		image[i] = al_create_bitmap(64, 64);
		if (!image[i]) {
			exit(1);
		}

		al_set_target_bitmap(image[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));

		al_draw_filled_rectangle(0, 25, 64, 39, al_map_rgb(75, 75, 75));
		al_draw_filled_rectangle(25, 0, 39, 64, al_map_rgb(50, 50, 50));
		al_draw_circle(32, 32, 8, al_map_rgb(0, 0, 0), 5);

		al_draw_line(0, 32, 64, 32, al_map_rgb(255, 100, 255), 2);
		al_draw_line(32, 0, 32, 64, al_map_rgb(255, 100, 255), 2);
		al_draw_circle(32, 32, 16, al_map_rgb(200, 200, 200), 5);


		x = 20;
		y = HEIGHT / 2;

		speed = 7;
		boundx = al_get_bitmap_width(image[i]);
		boundy = al_get_bitmap_height(image[i]);

		switch (i)
		{
		case 0: // up
			al_draw_filled_circle(32, 0, 5, al_map_rgb(247, 225, 40));
			break;
		case 1:// down
			al_draw_filled_circle(32, 64, 5, al_map_rgb(247, 225, 40));
			break;
		case 2:// left
			al_draw_filled_circle(0, 32, 5, al_map_rgb(247, 225, 40));
			break;
		case 3: // right
			al_draw_filled_circle(64, 32, 5, al_map_rgb(247, 225, 40));
			break;
		}
	}

}
void player::DrawPlayer(int flag)
{
	al_draw_bitmap(image[flag], x, y, 0);
}
void player::MoveUp(BadGuy BadGuys[], int count)
{
	y -= speed;
	if (!collides(BadGuys, count)) {
		y += speed;
	}
	if(y < 0)
		y = 0;
}
void player::MoveDown(int HEIGHT, BadGuy BadGuys[], int count)
{
	y += speed;
	if (!collides(BadGuys, count)) {
		y -= speed;
	}
	if(y > HEIGHT-boundy)
		y = HEIGHT-boundy;
}
void player::MoveLeft(BadGuy BadGuys[], int count)
{
	x -= speed;
	if (!collides(BadGuys, count)) {
		x += speed;
	}
	if(x < 0)
		x = 0;
}
void player::MoveRight(int WIDTH, BadGuy BadGuys[], int count)
{
	x += speed;
	if (!collides(BadGuys, count)) {
		x -= speed;
	}
	if(x > WIDTH-boundx)
		x = WIDTH-boundx;
}
bool player::collides(BadGuy BadGuys[], int count) {
	for (int j = 0; j < count; j++)
	{
		if (BadGuys[j].getLive())
		{
			if (x > (BadGuys[j].getX()  - BadGuys[j].getBoundX()) &&
				x < (BadGuys[j].getX() + BadGuys[j].getBoundX()) &&
				y >(BadGuys[j].getY() - BadGuys[j].getBoundY()) &&
				y < (BadGuys[j].getY() + BadGuys[j].getBoundY()))
			{
				return false;
			}
		}
	}

	return true;
}