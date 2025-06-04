#include "fish.h"

// constructors

fish::fish() {
	x = 0;
	y = 0;
	dir = 0;
	w = 140;
	h = 87;
	angle = 0;
	speed = 5;
	image = al_load_bitmap("fish.png");
}

fish::fish(int newx, int newy) {
	x = newx;
	y = newy;
	dir = 0;
	w = 140;
	h = 87;
	angle = 0;
	speed = 5;
	image = al_load_bitmap("fish.png");
}

// movement

void fish::moveUp() {
	if (y - (w/2) - speed <= 0) {
		y = 0 + (w/2);
	}
	y -= speed;
}

void fish::moveDown(int height) {
	if (y + h + speed >= height) {
		y = height - h;
	}
	y += speed;
}

void fish::moveLeft() {
	if (x - (h/2) - speed <= 0) {
		x = 0 + (h/2);
	}
	x -= speed;
}

void fish::moveRight(int width) {
	if (x + w + speed >= width) {
		x = width - (w/2);
	}
	else {
		x += speed;
	}
}

// getters

int fish::getX() { return x; }

int fish::getY() { return y; }

int fish::getSpeed() { return speed; }

// misc

void fish::drawFish(int width, int height, int flag) {
	// if sitting at the top or bottom of the screen
	if (x - (h/2) <= 0 && angle < 3.1) {
		// sitting at left side of screen
		angle += .1;
	}
	else if (x + w >= width && angle >= 0) {
		// sitting at right side of screen
		angle -= .1;
	}
	else if (y <= 0 + w && angle < 4.6) {
		// sitting at top of screen
		angle += .1;
	}
	else if (y >= height - h && angle > 1.6) {
		// sitting at bottom of screen
		angle -= .1;
	}
	switch (flag) {
	case 0:		// up
		al_draw_rotated_bitmap(image, w / 2, h / 2, x, y, angle, 0);
		break;
	case 1:		// down
		al_draw_rotated_bitmap(image, w / 2, h / 2, x, y, angle, 0);
		break;
	case 2:		// left
		al_draw_rotated_bitmap(image, w / 2, h / 2, x, y, angle, 0);
		break;
	case 3:		// right
		al_draw_rotated_bitmap(image, w / 2, h / 2, x, y, angle, ALLEGRO_FLIP_VERTICAL);
		break;
	}
}