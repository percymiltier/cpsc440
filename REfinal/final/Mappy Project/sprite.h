#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
using namespace std;

#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
	// friends
	friend int collided(int x, int y);
	friend bool endValue(int x, int y);
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void UpdateSprites();
	void DrawSprites(int xoffset, int yoffset);
	// movement
	void moveUp(int height, int blockheight);
	void moveDown(int height, int blockheight);
	void moveLeft(int width, int blockheight);
	void moveRight(int width, int blockheight);
	void takeHit();

	float getX() { return x; }
	float getY() { return y; }
	int getWidth() { return frameWidth; }
	int getHeight() { return frameHeight; }
	bool CollisionEndBlock();

	void setX(int newx) { x = newx; }
	void setY(int newy) { y = newy; }
	void setMoving(bool newm) { moving = newm; }
private:
	float x;
	float y;
	int speed;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int dir; // 0 = up, 1 = down, 2 = left, 3 = right
	bool moving;

	bool hit;
	int hittimer;
	int tint[3];

	int hp;

	ALLEGRO_BITMAP* image;
};

#endif