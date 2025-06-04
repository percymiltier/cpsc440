#ifndef WEAPONH
#define WEAPONH
#include "BadGuy.h"
#include "player.h"
class weapon
{
public:
	weapon();
	~weapon();
	void Drawweapon();
	void Fireweapon(player &Player, int direction);
	void Updateweapon(int WIDTH, int HEIGHT);
	void Collideweapon(BadGuy BadGuys[], int cSize);
private:
	int x;
	int y;
	int boundx;
	int boundy;
	bool live;
	int speed;
	float angle;
	ALLEGRO_BITMAP *image;
	int dir;
};
#endif
