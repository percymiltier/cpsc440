#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class player {
public:
	// constructors
	player();
	player(int newx, int newy);

	// misc
	void drawPlayer(int flag);
	void drawPointer();
	void moveLeft();
	void moveRight();
	void addPoint() { score++; }
	void takeHit() { health--; }

	// setters
	void setX(int newx) { x = newx; }
	void setY(int newy) { y = newy; }
	void setHealth(int newhp) { health = newhp; }
	void setScore(int newscore) { score = newscore; }

	// getters
	double getAngle() const { return angle; }
	int getX() const { return x; }
	int getY() const { return y; }
	int getBoundX() const { return boundX; }
	int getBoundY() const { return boundY; }
	int getHealth() const { return health; }
	int getScore() const { return score; }
private:
	double angle;
	int x, y, health, score, boundX, boundY, pointerW, pointerH;
	ALLEGRO_BITMAP* image[2];
	ALLEGRO_BITMAP* pointer;
};

#endif