#define _USE_MATH_DEFINES
#include <cmath>

#include "weapon.h"

// constructors
weapon::weapon() {
	x = 0;
	y = 0;
	speed = 5;
	live = false;
	image = al_load_bitmap("puyo.png");
	angle = 0;
}
weapon::~weapon() {
	al_destroy_bitmap(image);
}

// misc
// draw weapon to display
void weapon::drawWeapon() {
	if (live) {
		al_draw_bitmap(image, x, y, 0);
	}
}
// fire weapon
bool weapon::fireWeapon(player player) {
	if (!live) {
		x = player.getX() + (player.getBoundX() / 4);
		y = player.getY();
		live = true;
		return true;
	}
	return false;
}
// update weapon on screen
void weapon::updateWeapon(player player) {
	if (live) {
		x -= speed * cos(angle);
		y -= speed * sin(angle);
		if (al_get_bitmap_height(image) < 0) {
			live = false;
		}
	}
}
// hit enemy
void weapon::collideWeapon(enemy enemies[], int count, player* player) {
	if (live)
	{
		for (int j = 0; j < count; j++)
		{
			if (enemies[j].getLive())
			{
				if (x > (enemies[j].getX() - enemies[j].getBoundX()) &&
					x < (enemies[j].getX() + enemies[j].getBoundX()) &&
					y >(enemies[j].getY() - enemies[j].getBoundY()) &&
					y < (enemies[j].getY() + enemies[j].getBoundY()))
				{
					live = false;
					enemies[j].setLive(false);
					player->addPoint();
				}
			}
		}
	}
}
void weapon::setAngle(player player) {
	if (!live) {
		angle = player.getAngle();
		angle += 1.5;
	}
}