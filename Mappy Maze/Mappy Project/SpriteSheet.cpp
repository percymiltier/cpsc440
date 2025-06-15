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
	frameWidth = 32;
	frameHeight = 32;
	animationColumns = 3;
	animationRows = 1;
	animationDirection = 1;

	image = al_load_bitmap("carbuncle.bmp");
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
	if (y > (height - blockheight) || collided(x, y)) {
		// detect collision with border or wall
		y = oldy;
	}
	UpdateSprites();
}
void Sprite::moveDown(int height, int blockheight) {
	int oldy = y;
	y += speed;
	if (y < blockheight || collided(x, y)) {
		// detect collision with border or wall
		y = oldy;
	}
	UpdateSprites();
}
void Sprite::moveLeft(int width, int blockheight) {
	int oldx = x;
	x -= speed;
	if (x < blockheight || collided(x, y)) {
		// detect collision with border or wall
		x = oldx;
	}
	UpdateSprites();
}
void Sprite::moveRight(int width, int blockheight) {
	int oldx = x;
	x += speed;
	if (x < width - blockheight || collided(x, y)) {
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




