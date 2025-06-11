#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <stdio.h>
#include "Sprite.h"

#include <iostream>
using namespace std;

void sprite::drawSprite()
{
	if (spin) {
		al_draw_rotated_bitmap(image[curframe], width / 2, height / 2, x, y, angle, 0);
		angle += .1;
	}
	else if (scared && collision && timer < 3) {
		al_draw_tinted_bitmap(image[curframe], al_map_rgb(rand() % 255, rand() & 255, rand() % 255), x, y, 0);
		timer += 0.0166;
	}
	else if (baby && collision && timer < 10) {
		al_draw_scaled_bitmap(image[curframe], x, y, width, height, x, y, width / scale, height / scale, 0);
		timer += 0.0166;
	}
	else if (freeze && collision && timer < 5) {
		al_draw_bitmap(image[curframe], x, y, 0);
		timer += 0.0166;
	}
	else {
		al_draw_bitmap(image[curframe], x, y, 0);
		// reset timer
		timer = 0;
	}
}

void sprite::updatesprite()
{
	if (!(freeze && collision && timer < 5)) {
		//update x position
		if (++xcount > xdelay)
		{
			xcount = 0;
			x += xspeed;
		}

		//update y position
		if (++ycount > ydelay)
		{
			ycount = 0;
			y += yspeed;
		}
	}


	if (framecount++ > framedelay)
	{
		framecount = 0;
		curframe++;
		if (curframe >= maxframe)
			curframe = 0;
	}
}

void sprite::bouncesprite(int SCREEN_W, int SCREEN_H)
{
	//simple screen bouncing behavior
	if (x < 0)
	{
		x = 0;
		xspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (x > SCREEN_W - width)
	{
		x = SCREEN_W - width;
		xspeed = rand() % 2 - 6;
		animdir *= -1;
	}

	if (y < 0)
	{
		y = 0;
		yspeed = rand() % 2 + 4;
		animdir *= -1;
	}

	else if (y > SCREEN_H - height)
	{
		y = SCREEN_H -  height;
		yspeed = rand() % 2 - 6;
		animdir *= -1;
	}

}

void sprite::load_animated_sprite(int size)
{
	//load the animated sprite
	char s[80];
	maxframe=size;
	for (int n=0; n<size; n++)
	{
		sprintf_s(s, "eichi%d.png", n);
		image[n] = al_load_bitmap(s);

		al_convert_mask_to_alpha(image[n], al_map_rgb(255, 255, 255));
	}  
	width=al_get_bitmap_width(image[0]);
	height=al_get_bitmap_height(image[0]);
	curframe = 0;
	framedelay = 5;
	framecount = 0;


}

sprite::~sprite()
{
	for(int i = 0; i < maxframe; i++)
		al_destroy_bitmap(image[i]);
}

void sprite::detectCollision(sprite sprites[], int count, int SCREEN_W, int SCREEN_H) {
	bool temp = false;
	// detect collision with other sprites
	for (int i = 0; i < count; i++) {
		// dont want to compare to self
		if (this != &sprites[i]) {
			int otherX = sprites[i].getX();
			int otherY = sprites[i].getY();
			int otherBoundX = sprites[i].getWidth();
			int otherBoundY = sprites[i].getHeight();


			if (x > (otherX) && x < (otherX + otherBoundX) &&
				y > (otherY) && y < (otherY + otherBoundY))
			{
				// increase scale division if its a scaling sprite
				scale += 2;

				collision = true;
				x = rand() % SCREEN_W;
				y = rand() % SCREEN_H;
				temp = true;
				break;
			}
		}
	}
	// if there were no collision && no skills are running
	if (!temp) {
		if ((scared && timer < 3) || (baby && timer < 10) || (freeze && timer < 5)) {
			// do nothing
		}
		else {
			// if skills are done and there were no collissions, turn it off
			collision = false;
		}
	}
}

// setters
void sprite::setcollision(bool col) {
	collision = col;
}
void sprite::setSpin(bool spinning) {
	spin = spinning;
}
void sprite::setScared(bool scary) {
	scared = scary;
}
void sprite::setBaby(bool babymode) {
	baby = babymode;
}
void sprite::setFreeze(bool frozen) {
	freeze = frozen;
}
void sprite::setTime(int newtime) {
	timer = newtime;
}
