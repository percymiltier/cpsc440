#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include "ghost.h"

ghost::ghost()
{
	image = al_load_bitmap("ghost.png");
	live = false;
	speed = 5;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);


}
ghost::~ghost()
{
	al_destroy_bitmap(image);
}
void ghost::Drawghost()
{
	if(live)
	{
		float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

		al_draw_tinted_bitmap(image , al_map_rgba_f(r,g,b, 1), x,y, 0);
	}
}
void ghost::Startghost(int WIDTH, int HEIGHT )
{
	if(!live)
	{
		if(rand() % 500 == 0)
		{
			live = true;
			x = WIDTH;
			y = rand() % (HEIGHT-boundy);

		}
	}
}
void ghost::Updateghost()
{

	if(live)
	{
		x -= speed;
	}

}
void ghost::Collideghost(player &Player)
{
	if(live)
	{
		if( x - boundx < Player.getX() + Player.getBoundX() &&
			x + boundx > Player.getX() - Player.getBoundX() &&
			y - boundy < Player.getY() + Player.getBoundY() &&
			y + boundy > Player.getY() - Player.getBoundY())
		{
			Player.removeLife();
			live = false;
		}
		else if(x < 0)
		{
			live = false;
		}
	}
}