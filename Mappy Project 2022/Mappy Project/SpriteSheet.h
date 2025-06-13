#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;
class Sprite
{
	friend int collidedTL(int x, int y);
	friend int collidedTR(int x, int y);
	friend int collidedBL(int x, int y);
	friend int collidedBR(int x, int y);
	friend bool endValue( int x, int y );
public:
	Sprite();
	~Sprite();
	void InitSprites(int width, int height);
	void UpdateSprites(int width, int height, int dir); //dir 1 = right, 0 = left, 2 = Standing Still
	void DrawSprites(int xoffset, int yoffset);
	bool CollideSprite();
	float getX() {return x;}
	float getY() {return y;}
	int getWidth() {return frameWidth;}
	int getHeight() {return frameHeight;}
	int jumping(int jump, const int JUMPIT);
	bool CollisionEndBlock();

	void setIFJUMP(bool ifj) { ifjump = ifj; };

private:
	float x;
	float y;

	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;
	int frameWidth;
	int frameHeight;
	int animationColumns;
	int animationRows;
	int animationDirection;

	int lastjump;
	int walkmaxframe;
	bool ifjump;

	ALLEGRO_BITMAP *image;
};