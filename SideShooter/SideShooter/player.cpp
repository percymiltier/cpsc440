#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"


player::~player()
{
	for (int i = 0; i < 5; i++) {
		al_destroy_bitmap(image[i]);
	}
}
player::player(int HEIGHT)
{
	image[0] = al_load_bitmap("kirby0.png");
	image[1] = al_load_bitmap("kirby1.png");
	image[2] = al_load_bitmap("kirby2.png");
	image[3] = al_load_bitmap("kirby3.png");
	image[4] = al_load_bitmap("kirby4.png");
	x = 20;
	y = HEIGHT / 2;
	lives = 5;
	speed = 7;
	boundx = al_get_bitmap_width(image[0]);
	boundy = al_get_bitmap_height(image[0]);
	score = 0;
}
void player::DrawPlayer()
{
	switch (lives) {
	case 5:
		al_draw_bitmap(image[0], x, y, 0);
		break;
	case 4:
		al_draw_bitmap(image[1], x, y, 0);
		break;
	case 3:
		al_draw_bitmap(image[2], x, y, 0);
		break;
	case 2:
		al_draw_bitmap(image[3], x, y, 0);
		break;
	case 1:
		al_draw_bitmap(image[4], x, y, 0);
		break;
	case 0:
		// no more kirby
		break;
	}
}
void player::MoveUp()
{
	y -= speed;
	if(y < 0)
		y = 0;
}
void player::MoveDown(int HEIGHT)
{
	y += speed;
	if(y > HEIGHT)
		y = HEIGHT;
}
void player::MoveLeft()
{
	x -= speed;
	if(x < 0)
		x = 0;
}
void player::MoveRight()
{
	x += speed;
	if(x > 300)
		x = 300;
}
int player::getLives() {
	return lives;
}
int player::getScore() {
	return score;
}