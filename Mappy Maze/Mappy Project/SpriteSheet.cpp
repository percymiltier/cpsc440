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

	speed = 8;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 30;
	frameHeight = 30;
	animationColumns = 3;
	animationRows = 1;
	animationDirection = 1;

	image = al_load_bitmap("carbuncle.png");
}

bool Sprite::CollisionEndBlock()
{
	if (endValue(x + frameWidth/2, y + frameHeight + 5))
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
	if (collided(x, y)) {
		// detect collision with border or wall
		y = oldy;
	}
	UpdateSprites();
}
void Sprite::moveDown(int height, int blockheight) {
	int oldy = y;
	y += speed;
	if (collided(x, y + frameHeight)) {
		// detect collision with border or wall
		y = oldy;
	}
	UpdateSprites();
}
void Sprite::moveLeft(int width, int blockheight) {
	int oldx = x;
	x -= speed;
	if (collided(x, y)) {
		// detect collision with border or wall
		x = oldx;
	}
	UpdateSprites();
}
void Sprite::moveRight(int width, int blockheight) {
	int oldx = x;
	x += speed;
	if (collided(x + frameWidth, y)) {
		// detect collision with border or wall
		x = oldx;
	}
	UpdateSprites();
}

void Sprite::UpdateSprites() {
	frameCount++;
	if (frameCount > maxFrame) {
		frameCount = 0;
	}
}




