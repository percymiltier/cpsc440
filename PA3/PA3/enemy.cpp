#include "enemy.h"

// constructors
enemy::enemy() {
	x = 0;
	y = 0;
	speed = 5;
	live = false;
	image = al_load_bitmap("rin.png");
	boundX = al_get_bitmap_width(image);
	boundY = al_get_bitmap_height(image);
}
enemy::~enemy() {
	al_destroy_bitmap(image);
}

// misc
void enemy::drawEnemy() {
	if (live) {
		al_draw_bitmap(image, x, y, 0);
	}
}
void enemy::collideEnemy(player* player, int height) {
	if (live) {
		// hits below the player where the ground is
		if (y > height - 50)
		{
			live = false;
			player->takeHit();
		}
	}
}
void enemy::startEnemy(int width) {
	if (!live) {
		if (rand() % 1000 == 0) {		// 0.001% spawn rate on each frame
			live = true;
			y = 0 - boundY;
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