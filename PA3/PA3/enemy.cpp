#include "enemy.h"

// constructors
enemy::enemy() {
	x = 0;
	y = 0;
	speed = 5;
	live = false;
	image = al_load_bitmap("");
	boundX = al_get_bitmap_width(image);
	boundY = al_get_bitmap_height(image);
}
enemy::~enemy() {
	al_destroy_bitmap(image);
}

// misc
void enemy::drawEnemy() {
	al_draw_bitmap(image, x, y, 0);
}
void enemy::collideEnemy(player* player) {
	if (live) {
		if (x > (player->getX() - player->getBoundX()) &&
			x < (player->getX() + player->getBoundX()) &&
			y >(player->getY() - player->getBoundY()) &&
			y < (player->getY() + player->getBoundY()))
		{
			live = false;
			player->takeHit();
		}
	}
}
void enemy::startEnemy(int width) {
	if (!live) {
		if (rand() % 500 == 0) {		// 0.002% spawn rate on each frame
			live = true;
			y = 0;
			x = rand() % width - boundX;
		}
	}
}
void enemy::updateEnemy(int height) {
	if (live) {
		y += speed;
		if (y > height) {
			live = false;
		}
	}
}