#include "sprite.h"

#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5\allegro_acodec.h>
using namespace std;

Sprite::Sprite()
{
	image = NULL;
	sample = NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
	al_destroy_sample(sample);
}
void Sprite::InitSprites(int width, int height)
{
	x = 96;
	y = 96;

	speed = 5;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 34;
	frameHeight = 30;
	animationColumns = 3;
	moving = false;
	
	hit = false;
	hittimer = 0;
	tint[0] = 255;
	tint[1] = 255;
	tint[2] = 255;

	hp = 5;

	image = al_load_bitmap("carbuncle.png");
	sample = al_load_sample("hurtsound.wav");
	if (!sample) {
		exit(9);
	}
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + (frameWidth / 2), y + (frameHeight / 2)))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = 0;

	// change color on hit
	if (hit) {
		tint[0] = 255;
		tint[1] = 0;
		tint[2] = 0;
	}
	else {
		tint[0] = 255;
		tint[1] = 255;
		tint[2] = 255;
	}

	switch (dir) {
	case 0:
		// up
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, // region
			al_map_rgb(tint[0], tint[1], tint[2]),											// tint
			frameWidth/2, frameHeight/2,													// center
			x + (frameWidth / 2) - xoffset, y + (frameHeight / 2) - yoffset, 1, 1,			// destination + scale
			3,																			// rotate here
			0);																				//flags
		break;
	case 1:
		// down
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, // region
			al_map_rgb(tint[0], tint[1], tint[2]),											// tint
			frameWidth / 2, frameHeight / 2,												// center
			x + (frameWidth / 2) - xoffset, y + (frameHeight / 2) - yoffset, 1, 1,			// destination + scale
			0,																			// rotate here
			0);																				//flags
		break;
	case 2:
		// left
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, // region
			al_map_rgb(tint[0], tint[1], tint[2]),											// tint
			frameWidth / 2, frameHeight / 2,												// center
			x + (frameWidth / 2) - xoffset, y + (frameHeight/2) - yoffset, 1, 1,			// destination + scale
			1.5,																		// rotate here
			0);																				//flags
		break;
	case 3:
		// right
		al_draw_tinted_scaled_rotated_bitmap_region(image, fx, fy, frameWidth, frameHeight, // region
			al_map_rgb(tint[0], tint[1], tint[2]),											// tint
			frameWidth / 2, frameHeight / 2,												// center
			x + (frameWidth / 2) - xoffset, y + (frameHeight / 2) - yoffset, 1, 1,			// destination + scale
			4.5,																		// rotate here
			0);																				//flags
		break;
	}
}

// movement
void Sprite::moveUp(int height, int blockheight) {
	int oldy = y;
	y -= speed;
	if (collided(x + (frameWidth / 2), y)) {
		// detect collision with border or wall
		y = oldy;
	}
	dir = 0;
}
void Sprite::moveDown(int height, int blockheight) {
	int oldy = y;
	y += speed;
	if (collided(x + (frameWidth / 2), y + frameHeight)) {
		// detect collision with border or wall
		y = oldy;
	}
	dir = 1;
}
void Sprite::moveLeft(int width, int blockheight) {
	int oldx = x;
	x -= speed;
	if (collided(x, y + (frameHeight / 2))) {
		// detect collision with border or wall
		x = oldx;
	}
	dir = 2;
}
void Sprite::moveRight(int width, int blockheight) {
	int oldx = x;
	x += speed;
	if (collided(x + frameWidth, y + (frameHeight / 2))) {
		// detect collision with border or wall
		x = oldx;
	}
	dir = 3;
}

void Sprite::takeHit() {
	hp--;
	hit = true;
	hittimer = 0;
	al_play_sample(sample, 0.50, 0.0, 2.0, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void Sprite::UpdateSprites() {
	if (moving) {
		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}
	if (++hittimer > 60) {
		hit = false;
		hittimer = 0;
	}
}