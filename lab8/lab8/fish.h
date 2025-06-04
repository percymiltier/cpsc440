#pragma once
#ifndef FISH_H
#define FISH_H
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>

class fish {
public:
	// constructors
	fish();
	fish(int newx, int newy);

	// movement
	void moveUp();
	void moveDown(int height);
	void moveLeft();
	void moveRight(int width);

	// getters
	int getX();
	int getY();
	int getSpeed();

	// misc
	void drawFish(int width, int height, int flag);

private:
	int x, y, speed, dir, w, h;
	double angle;
	ALLEGRO_BITMAP* image;
};

#endif