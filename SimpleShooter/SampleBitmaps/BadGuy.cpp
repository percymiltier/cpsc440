#include "BadGuy.h"
BadGuy::~BadGuy()
{
	al_destroy_bitmap(image);
}
BadGuy::BadGuy()
{
	image = al_create_bitmap(64,64);   
	if(!image) {
		exit(1);
	}

	al_set_target_bitmap(image);
	al_clear_to_color(al_map_rgb(0, 0, 0));

	x = 0;
	y = 0;

	al_draw_filled_rectangle(25,10,39,54,al_map_rgb(100, 100, 120));
	al_draw_filled_ellipse(32,32,32,16,al_map_rgb(255, 0, 255));
	al_draw_filled_circle(32,32,4,al_map_rgb(255, 255, 255));
	al_draw_filled_circle(16,32,4,al_map_rgb(120, 255, 255));
	al_draw_filled_circle(48,32,4,al_map_rgb(255, 255, 120));
	boundx = al_get_bitmap_width(image)*.75;
	boundy = al_get_bitmap_height(image)*.75;
	live = false;

}
void BadGuy::DrawBadGuy()
{


	if(live)
	{
		al_draw_bitmap(image,x,y,0);
	}

}
void BadGuy::StartBadGuy(int WIDTH, int HEIGHT, BadGuy BadGuys[], int count)
{
	if (!live)
	{
		bool collision;
		const int buffer = 20; //buffer distance this relates to how big your bitmap is

		do {
			collision = false;
			x = rand() % (WIDTH - boundx);
			y = rand() % (HEIGHT - boundy);

			// Check for collision with other bad guys
			for (int i = 0; i < count; i++)
			{
				if (BadGuys[i].getLive() && &BadGuys[i] != this)
				{
					int otherX = BadGuys[i].getX();
					int otherY = BadGuys[i].getY();
					int otherBoundX = BadGuys[i].getBoundX();
					int otherBoundY = BadGuys[i].getBoundY();

					// buffer in collision check
					if (x > (otherX - otherBoundX - buffer) && x < (otherX + otherBoundX + buffer) &&
						y >(otherY - otherBoundY - buffer) && y < (otherY + otherBoundY + buffer))
					{
						collision = true;
						break;
					}
				}
			}
		} while (collision);
	}
	live = true;
}

