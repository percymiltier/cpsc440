#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "enemy.h"
#include "player.h"

#pragma once
#ifndef WEAPON_H
#define WEAPON_H

class weapon {
public:
	// constructors
	weapon();
	~weapon();

	// misc
	void drawWeapon();
	bool fireWeapon(player player);
	void updateWeapon(player player);
	void collideWeapon(enemy enemies[], int count, player* player);
	void setAngle(player player);

	// setters
	void setX(int newx) { x = newx; }
	void setY(int newy) {y = newy; }
	void setLive(bool newlive) { live = newlive; }
private:
	int x, y, speed;
	double angle;
	bool live;
	ALLEGRO_BITMAP* image;
};

#endif 