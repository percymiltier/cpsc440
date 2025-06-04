#ifndef PLAYERH
#define PLAYERH
#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include "BadGuy.h"

class player
{
public:
	player(int HEIGHT);
	~player();
	void DrawPlayer(int flag);
	void MoveUp(BadGuy BadGuys[], int count);
	void MoveDown(int HEIGHT, BadGuy BadGuys[], int count);
	void MoveLeft(BadGuy BadGuys[], int count);
	void MoveRight(int WIDTH, BadGuy BadGuys[], int count);
	int getBoundX(){return boundx;}
	int getBoundY(){return boundy;}
	int getX(){return x;}
	int getY(){return y;}
	bool collides(BadGuy BadGuys[], int count);
private:
	int x;
	int y;
	int speed;
	int boundx;
	int boundy;
	ALLEGRO_BITMAP *image[4];
};
#endif

