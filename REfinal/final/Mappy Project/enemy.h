#pragma once
#include "sprite.h"

#ifndef ENEMY_H
#define ENEMY_H

class enemy {
	// friends
	friend int collided(int x, int y);
public:
	enemy();
	~enemy();

	void loadEnemyMap();
	void initEnemy(bool living, int newx, int newy, int newspeed, int newtype);
	void updateEnemy();
	void drawEnemy(int xoffset, int yoffset);
	void hitSprite(Sprite* player);

	void setLive(bool newl) { live = newl; }
private:
	int x, y, width, height, speed;
	bool collision, live;
	int type; // 0 = horizontal, 1 = vertical
	int direction = 1; // flips directions for each enemy, can be -1 or 1

	ALLEGRO_BITMAP *image;
};

#endif