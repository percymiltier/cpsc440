#include "SpriteSheet.h"

Sprite::Sprite()
{
	image=NULL;
}
Sprite::~Sprite()
{
	al_destroy_bitmap(image);
}
void Sprite::InitSprites(int width, int height)
{
	x = 64;
	y = 64;

	speed = 4;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 34;
	frameHeight = 30;
	animationColumns = 3;
	moving = false;

	image = al_load_bitmap("carbuncle.png");
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + (frameWidth / 2), y + (frameHeight / 2)))
		return true;
	else
		return false;
}

void Sprite::DrawSprites(int xoffset, int yoffset)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = 0;

	al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - xoffset, y - yoffset, 0);
}

// movement
void Sprite::moveUp(int height, int blockheight) {
	int oldy = y;
	y -= speed;
	if (collided(x + (frameWidth / 2), y)) {
		// detect collision with border or wall
		y = oldy;
	}
	dir = 0;
}
void Sprite::moveDown(int height, int blockheight) {
	int oldy = y;
	y += speed;
	if (collided(x + (frameWidth / 2), y + frameHeight)) {
		// detect collision with border or wall
		y = oldy;
	}
	dir = 1;
}
void Sprite::moveLeft(int width, int blockheight) {
	int oldx = x;
	x -= speed;
	if (collided(x, y + (frameHeight / 2))) {
		// detect collision with border or wall
		x = oldx;
	}
	dir = 2;
}
void Sprite::moveRight(int width, int blockheight) {
	int oldx = x;
	x += speed;
	if (collided(x + frameWidth, y + (frameHeight / 2))) {
		// detect collision with border or wall
		x = oldx;
	}
	dir = 3;
}

void Sprite::UpdateSprites() {
	if (moving) {
		if (++frameCount > frameDelay) {
			frameCount = 0;
			if (++curFrame > maxFrame)
				curFrame = 1;
		}
	}
}




