#include "player.h"

// constructors
player::player() {
	for (int i = 0; i < 3; i++) {
		image[i] = NULL;
	}
}

player::~player() {
	for (int i = 0; i < 3; i++) {
		al_destroy_bitmap(image[i]);
	}
}

// misc
void player::initPlayer(int scrwidth, int scrheight) {
	// position
	x = scrwidth / 2;
	y = scrheight / 2;

	// bitmap setup
	image[0] = al_load_bitmap("1.png");
	image[1] = al_load_bitmap("2.png");
	image[2] = al_load_bitmap("3.png");
	width = 34;
	height = 30;
	anirow = 1;
	anicol = 3;
	maxframe = 3;
	curframe = 0;
	framecount = 0;
	framedelay = 6;

	// everything else
	hp = 5;
	speed = 5;
	moving = false;
}

void player::updatePlayer(int dir) {
	if (moving) {
		if (++framecount > framedelay) {
			framecount = 0;
			if (++curframe > maxframe)
				curframe = 1;
		}
	}
	direction = dir;
}

void player::drawPlayer(int xoff, int yoff) {
	{
		switch (direction) {
		case 0:
				// up
				al_draw_rotated_bitmap(image[framecount], width / 2, height / 2, x - xoff, y - yoff, 1.5, 0);
			case 1:
				// down
				al_draw_bitmap(image[framecount], x - xoff, y - yoff, 0);
				break;
			case 2:
				// left
				al_draw_rotated_bitmap(image[framecount], width / 2, height / 2, x - xoff, y - yoff, 1.5, 0);
			case 3:
				// right
				al_draw_rotated_bitmap(image[framecount], width / 2, height / 2, x - xoff, y - yoff, 1.5, 0);
		}

	}
}

bool player::CollisionEndBlock() {
	if (endValue(x + (width / 2), y + (height / 2))) {
		return true;
	}
	else {
		return false;
	}
}

void player::moveUp() {
	int oldy = y;
	y -= speed;
	if (y < 0) {
		// detect collision with border or wall
		y = oldy;
	}
	direction = 0;
}

void player::moveDown(int scrheight) {
	int oldy = y;
	y += speed;
	if (y > scrheight) {
		// detect collision with border or wall
		y = oldy;
	}
	direction = 1;
}

void player::moveLeft() {
	int oldx = x;
	x -= speed;
	if (x < 0) {
		// detect collision with border or wall
		x = oldx;
	}
	direction = 2;
}

void player::moveRight(int scrwidth) {
	int oldx = x;
	x += speed;
	if (x > scrwidth) {
		// detect collision with border or wall
		x = oldx;
	}
	direction = 3;
}