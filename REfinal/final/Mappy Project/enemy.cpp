#include "enemy.h"

#include <allegro5/allegro.h>
#include <allegro5\allegro_audio.h>
#include <iostream>
using namespace std;

enemy::enemy() {
	image = NULL;
}

enemy::~enemy() {
	al_destroy_bitmap(image);
}

void enemy::loadEnemyMap() {
	image = al_load_bitmap("enemy.png");
	if (!image) {
		fprintf(stderr, "Failed to load enemy.png\n");
		exit(-2);
	}
}

void enemy::initEnemy(bool living, int newx, int newy, int newspeed, int newtype) {
	live = living;
	x = newx;
	y = newy;
	speed = newspeed;
	type = newtype;

	width = 32;
	height = 32;
	collision = false;

}

void enemy::updateEnemy() {
	int oldx = x;
	int oldy = y;

	if (live) {
		switch (type) {
		case 0:
			// horizontal enemy
			x += speed * direction;
			if (collided(x + width, y) || collided(x, y)) {
				// detect collision with border or wall
				x = oldx;
				// flip movement
				if (direction == 1) {
					direction = -1;
				}
				else {
					direction = 1;
				}
			}
			break;
		case 1:
			// vertical enemy
			y += speed * direction;
			if (collided(x, y + height) || collided(x, y)) {
				// detect collision with border or wall
				y = oldy;
				// flip movement
				if (direction == 1) {
					direction = -1;
				}
				else {
					direction = 1;
				}
			}
			break;
		}
	}
}

void enemy::drawEnemy(int xoffset, int yoffset) {
	if (live) {
		al_draw_bitmap(image, x - xoffset, y - yoffset, 0);
	}
}

void enemy::hitSprite(Sprite* player) {
	// detect collision with player and take hp if hit, getting hit grants immunity
	if (!player->getHit()) {
		if (live) {
			if (x > player->getX() && x < (player->getX() + player->getWidth())
				&& y > player->getY() && y < (player->getY() + player->getHeight())) {
				player->takeHit();
			}
		}
	}
}