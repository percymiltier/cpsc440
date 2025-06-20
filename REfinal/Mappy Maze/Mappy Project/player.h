#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class player {
	// friends
	friend int collided(int x, int y);
	friend bool endValue(int x, int y);

public:

	// constructors
	player();
	~player();

	// misc
	void initPlayer(int scrwidth, int scrheight);
	void updatePlayer();
	void drawPlayer(int xoff, int yoff);
	bool CollisionEndBlock();

	// movement
	void moveUp(int height, int blockheight);
	void moveDown(int height, int blockheight);
	void moveLeft(int width, int blockheight);
	void moveRight(int width, int blockheight);

	// setter
	void setX(int newx) { x = newx; }
	void setY(int newy) { y = newy; }
	void setMoving(bool newm) { moving = newm; }

	// getter
	int getX() { return x; }
	int getY() { return y; }
	int getWidth() { return width; }
	int getHeight() { return height; }
private:
	int x, y, width, height;
	int maxframe, curframe, framecount, framedelay, anicol, anirow;
	int direction; // 0 = up, 1 = down, 2 = left, 3 = right
	int hp, speed;
	bool moving;

	ALLEGRO_BITMAP *image[3];
};

#endif