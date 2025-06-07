#define _USE_MATH_DEFINES
#include <cmath>

#include "weapon.h"

// constructors
weapon::weapon() {
	x = 0;
	y = 0;
	speed = 5;
	live = false;
	image = al_load_bitmap("");
}
weapon::~weapon() {
	al_destroy_bitmap(image);
}

// misc
// draw weapon to display
void weapon::drawWeapon() {
	al_draw_bitmap(image, x, y, 0);
}
// fire weapon
void weapon::fireWeapon(player player) {
	if (!live) {
		x = player.getX() - (player.getBoundX() / 2);
		y = player.getY() - (player.getBoundY() / 2);
		live = true;
	}
}
// update weapon on screen
void weapon::updateWeapon(player player) {
	if (live) {
		double radian_angle = ((player.getAngle() + 64.0) / 0.711) * ((2 * M_PI) / 360.0);
		x -= speed * cos(radian_angle);
		y -= speed * sin(radian_angle);
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