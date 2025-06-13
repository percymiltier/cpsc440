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
	x = 80;
	y = -10;


	maxFrame = 12;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 6;
	frameWidth = 50;
	frameHeight = 64;
	animationColumns = 8;
	animationRows = 2;
	animationDirection = 1;

	// additional variables
	lastjump = y;
	walkmaxframe = 8;

	image = al_load_bitmap("guy.bmp");
	al_convert_mask_to_alpha(image, al_map_rgb(255,0,255));
}

void Sprite::UpdateSprites(int width, int height, int dir)
{
	int oldx = x;
	int oldy = y;

	if(dir == 1){ //right key
		animationDirection = 1; 
		x+=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > walkmaxframe)
				curFrame=1;
		}
	} else if (dir == 0){ //left key
		animationDirection = 0; 
		x-=2; 
		if (++frameCount > frameDelay)
		{
			frameCount=0;
			if (++curFrame > walkmaxframe)
				curFrame=1;
		}
	}else //represent that they hit the space bar and that mean direction = 0
		animationDirection = dir;

	// jump
	if (lastjump > y) {
		// ascending
		curFrame = 10;
	}
	else if (lastjump < y) {
		// descending
		curFrame = 11;
	}
	if (ifjump && collidedTL(x, y)) {
		curFrame = 12;
		ifjump = false;
	}

	//check for collidedTL with foreground tiles
	if (animationDirection == 0)
	{ 
		if (collidedTL(x, y + frameHeight)) { //collision detection to the left
			x = oldx; 
			y= oldy;
		}

	}
	else if (animationDirection == 1)
	{ 
		if (collidedTL(x + frameWidth, y + frameHeight)) { //collision detection to the right
			x = oldx; 
			y= oldy;
		}
	}
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
	int fy = (curFrame / animationColumns) * frameHeight;
	if (curFrame > 7) {
		// jumping frame access
		int fy = frameHeight * 2;
	}

	if (animationDirection==1){
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, 0);
	}else if (animationDirection == 0 ){
		al_draw_bitmap_region(image, fx, fy, frameWidth,frameHeight, x-xoffset, y-yoffset, ALLEGRO_FLIP_HORIZONTAL);
	}else if (animationDirection == 2 ){
		al_draw_bitmap_region(image,0,0,frameWidth,frameHeight,  x-xoffset, y-yoffset, 0);

	}
}

int Sprite::jumping(int jump, const int JUMPIT)
{
	//handle jumping
	if (jump==JUMPIT) { 
		if (!collidedTL(x + frameWidth/2, y + frameHeight + 5))
			jump = 0; 
	}
	else
	{
		y -= jump/3; 
		jump--; 
		curFrame=0;
	}

	if (jump<0) 
	{ 
		if (collidedTL(x + frameWidth/2,  y + frameHeight))
		{ 
			jump = JUMPIT; 
			while (collidedTL(x + frameWidth/2,y + frameHeight))
			{
				y -= 3;
			}
		}

	}

	// keep jump from escaping map
	if (y < 0) {
		y = 0;
		jump = 0;
	}

	lastjump = y;
	return jump;
}