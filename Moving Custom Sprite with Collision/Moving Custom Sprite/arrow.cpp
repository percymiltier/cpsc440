#include "arrow.h"
arrowClass::arrowClass()
{
	speed=0;
	x=100;
	y=100;
	dir=1;
	score = 0;
	arrow_bmp[1] = NULL;
}
arrowClass::~arrowClass()
{
	for(int i=0; i<4; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
}
void arrowClass::drawArrow()
{
	al_draw_bitmap(arrow_bmp[0], getX(), getY(), 0);
}
void arrowClass::create_arrow_bitmap(ALLEGRO_DISPLAY *display)
{
	// bitmap creation
	arrow_bmp[0] = al_create_bitmap(64, 64);
	if (!arrow_bmp[0]) {
		exit(1);
		al_destroy_display(display);
	}

	al_set_target_bitmap(arrow_bmp[0]);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	int x = 32;
	int y = 20;


	// all my primatives
	al_draw_filled_ellipse(x, y, 8, 20, al_map_rgb(137, 137, 137));
	al_draw_filled_circle(x, y - 5, 5, al_map_rgb(115, 196, 242));
	al_draw_filled_triangle(x, y + 20, x + 12, y + 20, x + 12, y + 40, al_map_rgb(229, 38, 38));
	al_draw_filled_triangle(x, y + 20, x - 12, y + 20, x - 12, y + 40, al_map_rgb(229, 38, 38));
	al_draw_filled_rectangle(x - 5, y + 20, x + 5, y + 25, al_map_rgb(229, 38, 38));
	al_draw_filled_circle(x, y + 32, 5, al_map_rgb(255, 239, 74));
	al_draw_filled_triangle(x - 5, y + 32, x + 5, y + 32, x, y + 45, al_map_rgb(255, 239, 74));
}
void arrowClass::erase_arrow()
{

	int left = x ;
	int top = y;
	int right = x + 64;
	int bottom =y + 64;

	al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void arrowClass::up()
{
	dir=0;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::down()
{
	dir=2;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}


void arrowClass::left()
{
	dir=3;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}

void arrowClass::right()
{
	dir=1;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}
int arrowClass::getDirection()
{
	return dir;
}
int arrowClass::getSpeed()
{
	return speed;
}
int arrowClass::getX()
{
	return x;
}
int arrowClass::getY()
{
	return y;
}
void arrowClass::move_arrow(int width, int height)
{

	//update arrow position based on direction
	switch(dir)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		x += speed;
		break;
	case 2:
		y += speed;
		break;
	case 3:
		x -= speed;
	}

	//keep arrow inside the screen
	if (x > width-64)
	{
		x = width-64;
		speed = 0;
	}
	if (x < 0)
	{
		x = 0;
		speed = 0;
	}
	if (y > height-64)
	{
		y = height-64;
		speed = 0;
	}
	if (y < 0)
	{
		y = 0;
		speed = 0;
	}
}
