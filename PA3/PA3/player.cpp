#include "player.h"

// constructors
player::player() {
	angle = 1.5;
	x = 0;
	y = 0;
	score = 0;
	health = 5;
	image[0] = al_load_bitmap("");
	image[1] = al_load_bitmap("");
	boundX = al_get_bitmap_width(image[0]);
	boundY = al_get_bitmap_height(image[0]);

	pointer = al_load_bitmap("");
	pointer = al_load_bitmap("");
	pointerW = al_get_bitmap_width(pointer);
	pointerH = al_get_bitmap_height(pointer);
}
player::player(int newx, int newy) {
	angle = 1.5;
	x = newx;
	y = newy;
	score = 0;
	health = 5;
	image[0] = al_load_bitmap("");
	image[1] = al_load_bitmap("");
	boundX = al_get_bitmap_width(image[0]);
	boundY = al_get_bitmap_height(image[0]);

	pointer = al_load_bitmap("");
	pointerW = al_get_bitmap_width(pointer);
	pointerH = al_get_bitmap_height(pointer);
}

// misc
// draw player to display
void player::drawPlayer(int flag) {
	// 0 = neutral
	// 1 = firing
	al_draw_bitmap(image[flag], x, y, 0);
}
// draw pointer to display
void player::drawPointer() {
	al_draw_rotated_bitmap(pointer, (pointerW / 2), pointerW, x, y - pointerH / 2, angle, 0);
}
// move pointer left
void player::moveLeft() {
	angle -= .1;
	if (angle < .2) {
		angle = .2;
	}
}
// move pointer right
void player::moveRight() {
	angle += .1;
	if (angle > 3.3) {
		angle = 3.3;
	}
}