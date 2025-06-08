#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "player.h"

#pragma once
#ifndef ENEMY_H
#define ENEMY_H

class enemy {
public:
	// constructors
	enemy();
	~enemy();

	// misc
	void drawEnemy();
	void collideEnemy(player* player, int height);
	void startEnemy(int width);
	void updateEnemy(int height);

	// setters
	void setX(int newx) { x = newx; }
	void setY(int newy) { y = newy; }
	void setLive(bool newlive) { live = newlive; }

	// getters
	int getX() { return x; }
	int getY() { return y; }
	int getBoundX() { return boundX; }
	int getBoundY() { return boundY; }
	bool getLive() { return live; }
private:
	int x, y, speed, boundX, boundY;
	bool live;
	ALLEGRO_BITMAP* image;
};

#endif
